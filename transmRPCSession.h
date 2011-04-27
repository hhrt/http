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
  TransmRpcSession();
  bool setConnectionSettings(QString h="127.0.0.1", QString p="9091", QString u="/transmission/rpc");
  int openSession();
  void closeSession();
  bool getTorrentsList(std::vector<unsigned int> ids, std::vector<std::string> fileds);

  private:
  QHttp *http;
  QBuffer *recieved;
  QString transmSessionId;
  QByteArray request;
  QString host;
  QString port;
  QString url;

  private slots:
  void dataRecieved();

  signals:
  void HttpError(int errorCode);
  void receivedTorrentsList(TorrentsList torrentsList);

};

#endif
