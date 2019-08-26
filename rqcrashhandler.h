#ifndef RQCRASHHANDLER_H
#define RQCRASHHANDLER_H

#include <QNetworkReply>
#include <QObject>
#include <QQmlEngine>
#include <QSettings>

class QBreakpadHttpUploader;

class RQCrashHandler : public QObject {
  Q_OBJECT
public:
  static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

  RQCrashHandler(RQCrashHandler const &) = delete;
  void operator=(RQCrashHandler const &) = delete;

  Q_INVOKABLE void init(const QVariantMap &options);
  Q_INVOKABLE void addExtraParameter(const QString &key, const QString &value);
  Q_INVOKABLE void addExtraParameter(const QString &key,
                                     const QVariantMap &value);
  Q_INVOKABLE void removeExtraParameter(const QString &key);
  Q_INVOKABLE QVariantMap getParameters() const;
  Q_INVOKABLE QString getLastCrashReport() const;
  Q_INVOKABLE bool hasPendingUpload() const;
  Q_INVOKABLE void sendCrashReport(const QString &crashId);

  Q_INVOKABLE QUrl getSubmitURL() const;
  Q_INVOKABLE QString getProductName() const;
  Q_INVOKABLE QString getCompanyName() const;
  Q_INVOKABLE bool getUploadToServer() const;
  Q_INVOKABLE bool getAutoupload() const;

  Q_INVOKABLE bool isRestartedAfterCrash() const;

  Q_INVOKABLE void crash();

  void writeCrashReport(const QString &crashId);

signals:
  void uploadFailed(const QNetworkReply::NetworkError &err);
  void uploadSucceeded(const QString &data);

private slots:
  void onUploadFinished(QNetworkReply::NetworkError err, QString data);

private:
  bool writeParametersToDisk(const QString &crashId);
  QMap<QString, QString> readParametersFromDisk(const QString &crashId);
  bool removeParametersFile(const QString &crashId);

private:
  RQCrashHandler();

  QUrl m_submitURL;
  QString m_productName;
  QString m_companyName;
  bool m_uploadToServer;
  bool m_autoupload;
  QVariantMap m_extra;
  QString m_crashDirPath;
  QSettings m_settings;
  QBreakpadHttpUploader *m_uploader;
};

#endif // RQCRASHHANDLER_H
