#include "rqcrashhandler.h"

#include "QBreakpadHttpUploader.h"

#include "qt_breakpad.h"
#include <QString>
#include <QUrl>
#include <QtCore>

namespace {
#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX) || defined(Q_OS_WIN32) ||       \
    defined(Q_OS_IOS)
const bool kSupported = true;
#else
const bool kSupported = false;
#endif
} // namespace

// qml instance, singleton for qml
QObject *RQCrashHandler::qmlInstance(QQmlEngine *engine,
                                     QJSEngine *scriptEngine) {
  Q_UNUSED(engine);
  Q_UNUSED(scriptEngine);

  static RQCrashHandler instance;
  QQmlEngine::setObjectOwnership(&instance, QQmlEngine::CppOwnership);

  return &instance;
}

// breakpad callback
static bool qtBreakpadCallback(QFile &minidumpFile, void *context) {
  RQCrashHandler *handler = (RQCrashHandler *)context;

  QFileInfo fileInfo(minidumpFile);

  bool uploadToServer = handler->getUploadToServer();
  if (!uploadToServer) {
    return true;
  }

  // write dump extradata to disk
  QString crashId = fileInfo.baseName();
  handler->writeCrashReport(crashId);

// restart and send dump
// https://stackoverflow.com/questions/5129788/how-to-restart-my-own-qt-application
#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX) || defined(Q_OS_WIN32)
  auto programName = qApp->arguments()[0];
  auto args = qApp->arguments();
  QProcess::startDetached(programName, args);
#else
  qApp->quit();
#endif

  return true;
}

// class impl
RQCrashHandler::RQCrashHandler()
    : QObject(), m_submitURL(), m_productName(), m_companyName(),
      m_uploadToServer(true), m_extra(), m_crashDirPath(), m_settings(),
      m_uploader(new QBreakpadHttpUploader()) {}

void RQCrashHandler::init(const QVariantMap &options) {
  if (!kSupported) {
    qWarning() << "Unsupported platform";
    return;
  }

  m_productName =
      options.value("productName", qApp->applicationName()).toString();
  m_companyName =
      options.value("companyName", qApp->organizationName()).toString();
  m_submitURL = QUrl::fromUserInput(options.value("submitURL").toString());
  m_uploadToServer = options.value("uploadToServer", true).toBool();

  if (m_uploadToServer && !m_submitURL.isValid()) {
    qFatal("Invalid submitURL");
  }

  m_extra = options.value("extra").toMap();

  // create crash folder, it not exists
  QString crash_dir_name = m_productName + " Crashes";
  m_crashDirPath =
      QDir::cleanPath(QDir::tempPath() + QDir::separator() + crash_dir_name);
  QDir crash_dir = QDir(m_crashDirPath);
  if (!crash_dir.exists() && !crash_dir.mkpath(".")) {
    qFatal(QString("Unable to create folder %1").arg(crash_dir_name).toUtf8());
  }

  if (hasPendingUpload()) {
    QString crashId = getLastCrashReport();
    sendCrashReport(crashId);
  }

  QtBreakpad::init(m_crashDirPath, qtBreakpadCallback, this);
}

void RQCrashHandler::addExtraParameter(const QString &key,
                                       const QString &value) {
  m_extra.insert(key, value);
}

void RQCrashHandler::addExtraParameter(const QString &key,
                                       const QVariantMap &value) {
  QJsonDocument doc = QJsonDocument::fromVariant(value);
  m_extra.insert(key, doc.toJson());
}

void RQCrashHandler::removeExtraParameter(const QString &key) {
  m_extra.remove(key);
}

QVariantMap RQCrashHandler::getParameters() const { return m_extra; }

void RQCrashHandler::crash() {
  int *a = (int *)0x42;

  fprintf(stdout, "Going to crash...\n");
  fprintf(stdout, "A = %d", *a);
}

void RQCrashHandler::writeCrashReport(const QString &crashId) {
  writeParametersToDisk(crashId);

  m_settings.beginGroup("CrashReport");
  m_settings.setValue("pendingUpload", true);
  m_settings.setValue("lastCrashId", crashId);
  m_settings.endGroup();
}

void RQCrashHandler::onUploadFinished(QNetworkReply::NetworkError err,
                                      QString data) {
  Q_UNUSED(data)
  if (err == QNetworkReply::NoError) {
    // success
    m_settings.setValue("CrashReport/pendingUpload", false);
    emit uploadSucceeded(data);
  } else {
    emit uploadFailed(err);
  }
}

QString RQCrashHandler::getLastCrashReport() const {
  return m_settings.value("CrashReport/lastCrashId", "").toString();
}

bool RQCrashHandler::hasPendingUpload() const {
  return m_settings.value("CrashReport/pendingUpload", false).toBool();
}

bool RQCrashHandler::writeParametersToDisk(const QString &crashId) {
  QFile file(
      QDir::cleanPath(m_crashDirPath + QDir::separator() + crashId + ".json"));
  if (file.open(QFile::ReadWrite)) {
    QTextStream ts(&file);
    QJsonDocument doc = QJsonDocument::fromVariant(m_extra);
    ts << doc.toJson();
    return true;
  }

  return false;
}

QMap<QString, QString>
RQCrashHandler::readParametersFromDisk(const QString &crashId) {
  QMap<QString, QString> results;
  QFile file(
      QDir::cleanPath(m_crashDirPath + QDir::separator() + crashId + ".json"));
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    auto content = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(content);
    if (doc.isObject()) {
      QJsonObject obj = doc.object();
      for (QJsonObject::const_iterator iter = obj.begin(); iter != obj.end();
           ++iter) {
        QString key = iter.key();
        QJsonValue value = iter.value();
        QJsonDocument doc;
        if (value.isObject()) {
          doc.setObject(value.toObject());
        } else if (value.isArray()) {
          doc.setArray(value.toArray());
        }
        results.insert(key, doc.toJson());
      }
    }
  }

  return results;
}

bool RQCrashHandler::removeParametersFile(const QString &crashId) {
  QFile file(
      QDir::cleanPath(m_crashDirPath + QDir::separator() + crashId + ".json"));
  return file.remove();
}

void RQCrashHandler::sendCrashReport(const QString &crashId) {
  QFile minidumpFile(
      QDir::cleanPath(m_crashDirPath + QDir::separator() + crashId + ".dmp"));
  QFileInfo fileInfo(minidumpFile);
  QMap<QString, QString> extra = readParametersFromDisk(crashId);

  if (!fileInfo.exists()) {
    return;
  }

  QList<QHttpPart> extra_parts;

  foreach (auto key, extra.keys()) {
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader,
                   QString("form-data; name=\"%1\"").arg(key));
    part.setBody(extra.value(key).toUtf8());
    extra_parts.append(part);
  }

  m_uploader->setUrl(m_submitURL);
  m_uploader->uploadDump(fileInfo.absoluteFilePath(), extra_parts);

  connect(m_uploader, &QBreakpadHttpUploader::finished, this,
          &RQCrashHandler::onUploadFinished);
  connect(m_uploader, &QBreakpadHttpUploader::finished,
          [=]() { this->removeParametersFile(crashId); });
}

QUrl RQCrashHandler::getSubmitURL() const { return m_submitURL; }

QString RQCrashHandler::getProductName() const { return m_productName; }

QString RQCrashHandler::getCompanyName() const { return m_companyName; }

bool RQCrashHandler::getUploadToServer() const { return m_uploadToServer; }

// qml registration
void registerRQCrashHandler() {
  qmlRegisterSingletonType<RQCrashHandler>("ReactQML", 1, 0, "RQCrashHandler",
                                           &RQCrashHandler::qmlInstance);
}

Q_COREAPP_STARTUP_FUNCTION(registerRQCrashHandler)
