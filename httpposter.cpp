#include <QBuffer>
#include <QFile>
#include <QHttp>
#include <QUrl>
#include <QDebug>
#include "httpposter.h"

#define jsonRequestFileName "./request.json"

HttpPoster::HttpPoster( bool dbg = false)
{
  debug = dbg;
  http = new QHttp();
  connect(http, SIGNAL(done(bool)), this, SLOT(dataRecieved(bool)));
  jsonRecieved = new QBuffer();
  transmissionSessionId = "";

};

bool HttpPoster::setConnectionSettings(QString host, QString port) {

  requestHeader.setRequest("POST", "/transmission/rpc");
  requestHeader.setValue(host, port);

  QFile requestFile(jsonRequestFileName);
  if(!requestFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
	if(debug) qDebug() << "Error opening file " << jsonRequestFileName << " with json query content!\n";
	requestFile.close();
	emit httpPostError(fileOpenError);
    return false;
  }
  jsonRequest = requestFile.readAll();
  
  http->setHost("127.0.0.1", 9091);

  if(debug) qDebug() << "******* Request body: ********\n" << jsonRequest.data();

  requestFile.close();
  return true;
}

bool HttpPoster::sendRequest() {
  jsonRecieved->open(QBuffer::ReadWrite);

  requestHeader.setValue("X-Transmission-Session-Id", transmissionSessionId);
  http->request(requestHeader, jsonRequest, jsonRecieved);


  return true;
};

void HttpPoster::dataRecieved(bool error) {
  if(error) { 
	if(debug) qDebug() << "Error recieving data!" << "\n";
	emit httpPostError(dataRecievingError);
  }
  else {  

	if(debug) qDebug() << "\n******* Respose header: *******\n" << http->lastResponse().toString().toAscii().data();

	switch(http->lastResponse().statusCode()) {
      case 409:
	    transmissionSessionId = http->lastResponse().value("X-Transmission-Session-Id");
	    jsonRecieved->close();
	    jsonRecieved->buffer().clear();
	    sendRequest();
	  break;
	  case 200:
        jsonRecieved->seek(0);
	    if(debug) qDebug() << "******* Response body: *******\n" << jsonRecieved->buffer().data();
	    emit sendJsonData(jsonRecieved->buffer().data());
        jsonRecieved->close();
	  break;
	  default:
	    if(debug) qDebug() << "Response status code: " << http->lastResponse().statusCode();
	    jsonRecieved->close();
		jsonRecieved->buffer().clear();
		emit httpPostError(connectionError);
    }
  }
};
