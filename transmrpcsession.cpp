#include "transmrpcsession.h"
#include "json/json.h"
#include "tags.h"
#include <QHttp>
#include "torrent.h"

TransmRpcSession::TransmRpcSession(QString h = "127.0.0.1", QString p = "9091", QString u = "/transmission/rpc/") {
  host = h;
  port = p;
  url = u;
  http = new QHttp();
  connect(http, SIGNAL(done(bool)), thism SLOT(dataRecieved(bool)));
  received = new QBuffer;
  transmSessionId = "";
  http->setHost(host, port.toInt());
  sessionOpened = false;
};

TransmRpcSession::setConnectionSettings(QString h = this.Host, QString p = this.Port, QString u = this.Url) {
  host = h;
  port = p;
  url = u;
  http->setHost(host, port.toInt());
};

int TransmRpcSession::getTorrentsList(std::vector<unsigned int> ids, std::vector<std::string> fileds){
  //json request genereting
  std::ostringstream requestBodyTmp;//Fucking std::string doen't concatenates with int!!!
  requestBodyTmp << "{ \"arguments\" : { \"fields\" : [ ";
  int i;
  for(i=0;i<fields.size()-1;i++) 
    requestBodyTmp << "\" " << fields[i] << "\", ";
  requestBodyTmp << fields[i] << "\" ], ";
  requestBodyTmp << "\"ids\" : [ ";
  for(i=0;i<ids.size()-1;i++)
    requestBodyTmp << ids[i] << ", ";
  requestBodyTmp << ids[i] << " ] }, ";
  requestBodyTmp << " }, \"method\" : \"torrent-get\",\n \"tag\" : " << TORRENTSLIST << " }";
  requestBody = requestBodyTmp.str();
  //-----------------------

  requestHeader.setRequest("POST", Url);
  requestHeader.setValue(Host, Port);
  requestHeader.setValue("X-Transmission-Session-Id", transmissionSessionId);
  return http->request(requestHeader, requestBody, response);
};

void TransmRpcSession::dataReceived(bool error) {
  if(error) {
    qDebug() << "Error recieving data!" << http->errorString();
    emit httpError(dataRecievingError);
  }
  else {
    switch(http->lastResponse().statusCode()) {
      case 409:
	  transmissionSessionId = http->lastResponse().value("X-Transmission-Session-Id");
	  requestHeader.setValue("X-Transmission-Session-Id", transmissionSessionId);
	  response.close();
	  response.buffer().clear(); 
	  http->request(requestHeader, requestBody, response);//check this!!!
	  break;
	  case 200:
	  response.seek(0);
      if(parseRequestData())
        emit requestCompete();
	  else
		emit parsingDataError();
	  break;
	  default:
	  qDebug << "Response status code: " << http->lastResponse().statusCode();
	  response.close();
	  response.buffer().clear();
	  emit httpError(connectionError);

	}
  };
};

bool TransmRpcSession::parseRequestData() {

  Json::reader reader;
  Json::Value root;  
  Json::Value torrentsValue;

  if(!reader.parse(response.toAscii().data(), root)) {
	qDebug << "Error parsong JSON data!";
	return false;
  }

  torrentsValue = root["arguments"]["torrents"];
  if(torrentsValue.isNull()) {
	qDebug << "Request doesn't contains 'torretns' part!";
	return false;
  }

  Torrent *torrent;

  *torrentsList.result() = root.get("result", "none").asString();
  *torrentsList.tag() = root.get("tag", "0").asUInt();

  unsigned int i;
  for(i=0;i<torrentsValue.size();i++) {
    torrent = new Torrent(torrentValue[i]);
	torrentsList.torrents()->push_back(*torrent);
	delete torrent;
  }
  return true;
};
