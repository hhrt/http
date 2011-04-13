#ifndef HTTPPOSTER_H
#define HTTPPOSTER_H

#include <QObject>
#include <QHttp>

#include "errorcodes.h"

class QBuffer;
class QHttp;

class HttpPoster : public QObject
{

  Q_OBJECT

  public:
  HttpPoster( bool dbg );
  bool setConnectionSettings(QString host = "127.0.0.1", QString port = "80");
  bool sendRequest();

  private:
  QHttp *http;
  QBuffer *jsonRecieved;
  QString transmissionSessionId;
  QByteArray jsonRequest;
  QHttpRequestHeader requestHeader;
  bool debug;

  private slots:
  void dataRecieved(bool error);

  signals:
  void sendJsonData(QString jsonData);
  void httpPostError(int errorCode);
};

#endif
