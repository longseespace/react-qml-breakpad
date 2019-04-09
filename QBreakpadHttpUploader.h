/*
 *  Copyright (C) 2009 Aleksey Palazhchenko
 *  Copyright (C) 2014 Sergey Shambir
 *  Copyright (C) 2016 Alexander Makarov
 *
 * This file is a part of Breakpad-qt library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef QBREAKPAD_HTTP_SENDER_H
#define QBREAKPAD_HTTP_SENDER_H

#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QPointer>

class QString;
class QUrl;
class QFile;

class QBreakpadHttpUploader : public QObject {
  Q_OBJECT
public:
  QBreakpadHttpUploader(QObject *parent = nullptr);
  QBreakpadHttpUploader(const QUrl &url, QObject *parent = nullptr);
  ~QBreakpadHttpUploader();

  // TODO: proxy, ssl
  QString remoteUrl() const;
  void setUrl(const QUrl &url);

  bool uploading() const;

signals:
  void finished(QNetworkReply::NetworkError err, QString answer);
  void uploadProgress(qint64 sent, qint64 total);

public slots:
  void uploadDump(const QString &abs_file_path,
                  const QList<QHttpPart> &form_data);

private slots:
  void onUploadProgress(qint64 sent, qint64 total);
  void onError(QNetworkReply::NetworkError err);
  void onUploadFinished();

private:
  QNetworkAccessManager m_manager;
  QNetworkRequest m_request;
  QPointer<QNetworkReply> m_reply;
  QFile *m_file;
  bool m_uploading;
};

#endif // QBREAKPAD_HTTP_SENDER_H
