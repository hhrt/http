#ifndef TRANSMRPCSESSION
#define TRANSMRPCSESSION

#include<QObject>
#include<string>
#include<vector>

#include "errorcodes.h"

class QHttp;
class QBuffer;
class QString;
class TorrentsList;

class TransmRpcSession : public QObject {

  Q_OBJECT

  public:
  TransmRpcSession(QString h, QString p, QString u);
  bool setConnectionSettings(QString h, QString p, QString u);
  int getTorrentsList(std::vector<unsigned int> ids, std::vector<std::string> fileds);

  private:
  TorrentsList torrentsList;
  QHttp *http;
  QBuffer *response;
  QString transmSessionId;
  QByteArray request;
  QString host;
  QString port;
  QString url;
  QHttpRequestHeader requestHeader;
  QString requestBody;

  bool parseRequestData();

  private slots:
  void dataReceived();

  signals:
  void httpError(int errorCode);
  void parsingDataError();
  void requestComplete(); 

};

#endif
