#include "transmrpcsession.h"
#include "json/json.h"
#include <boost/lexical_cast.hpp>
#include "tags.h"
#include <QHttp>

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

bool TransmRpcSession::openSession() {

  

  return true;

};

int getTorrentsList(std::vector<unsigned int> ids, std::vector<std::string> fileds){
  //json request genereting
  requestBody = "{ \"arguments\" : { \"fields\" : [ ";
  int i;
  for(i=0;i<fields.size()-1;i++) 
    requestBody = requestBody + "\" " + fields[i] + "\", ";
  requestBody += fields[i] + "\" ], ";
  requestBody += "\"ids\" : [ ";
  for(i=0;i<ids.size()-1;i++)
    requestBody = requestBody + boost::lexical_cast<std::string>(ids[i]) +", ";
  requestBody += boost::lexical_cast<std::string>(ids[i]) + " ] }, ";
  requestBody = requestBody + " }, \"method\" : \"torrent-get\",\n \"tag\" : " + TORRENTSLIST +" }";
  //-----------------------

  requestHeader.setRequest("POST", Url);
  requestHeader.setValue(Host, Port);
  requestHeader.setValue("X-Transmission-Session-Id", transmissionSessionId);
  return http->request(requestHeader, requestBody, response);
};

void dataReceived(bool error) {
  if(error) {
    qDebug() << "Error recieving data!" << http->errorString();
    emit HttpError(int errorCode);
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

	}
  };
};
