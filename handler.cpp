#include<QObject>
#include<QStringList>
#include<QDebug>
#include<iostream>
#include<string>
#include<vector>
#include "handler.h"
#include "errorcodes.h"
#include "transmrpcsession.h"

Handler::Handler(QStringList args) {
  
  QString host;
  QString port;
  QString  url;

  if(args.contains("-h"))
  host = args[args.indexOf("-h")+1];
  if(args.contains("-p"))
  port = args[args.indexOf("-p")+1];
  if(args.contains("-u"))
  url  = args[args.indexOf("-u")+1];

  session = new TransmRpcSession(host, port, url);
  connect(session, SIGNAL(errorSignal(int)), this, SLOT(errorHandler(int)));
  connect(session, SIGNAL(requestComplete()), this, SLOT(successHandler()));

  std::vector<std::string> fields;
  std::vector<unsigned int> ids;
  fields.push_back("id");
  fields.push_back("name");
  fields.push_back("totalSize");
  ids.push_back(1);
  ids.push_back(2);

  session->getTorrentsList(ids, fields);

};

void Handler::errorHandler(int errorCode) {

  switch(errorCode) {
    case connectionError:
	qDebug() << "Connection error!";
	break;
	case dataRecievingError:
	qDebug() << "Data recieving error!";
	break;
	case parsingError:
	qDebug() << "Data parsing error!";
	break;
	default:
	qDebug() << "Error!";
  }
  exit(errorCode);
};

void Handler::successHandler() {

  std::cout << "Result     :" << *(session->content().result()) << "\n"; 
  std::cout << "Tag        :" << *(session->content().tag()) << "\n";
  std::cout << "Torrents(" << session->content().torrents()->size() << "):\n";
  unsigned int i;
  for(i=0; i < session->content().torrents()->size(); i++) {
	std::cout << "ID: " << *(session->content().torrents()->at(i).id());
	std::cout << " Name: \"" << *(session->content().torrents()->at(i).name()) << "\"";
	std::cout << " Size: " << (unsigned int)*(session->content().torrents()->at(i).size()) << "\n";
  }
  exit(0);
};
