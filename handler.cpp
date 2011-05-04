#include<QObject>
#include<QStringList>
#include<QDebug>
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
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
  fields.push_back("id");
  fields.push_back("name");
  fields.push_back("totalSize");
  unsigned int ids[] = {2, 1};

  session->getTorrentsList(fields, ids);

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

  std::cout << "Result     : " << *(session->content().result()) << "\n"; 
  std::cout << "Tag        : " << *(session->content().tag()) << "\n";
  std::cout << "Torrents(" << session->content().torrents()->size() << "):\n";
  unsigned int i;
  unsigned int size = 5;
  for(i=0;i < session->content().torrents()->size(); i++) 
	size = size < session->content().torrents()->at(i).name().length() ? session->content().torrents()->at(i).name().length() : size;
  for(i=0; i < session->content().torrents()->size(); i++) {
   std::cout << "ID: " << std::setw(3) << std::right << session->content().torrents()->at(i).id();
   std::cout << std::left << " Name: " << std::setw(size+2) << ("\"" + session->content().torrents()->at(i).name() + "\"");
   std::cout << " Size: " <<  std::setw(6) << std::right << session->content().torrents()->at(i).size() << "\n";
  }
  exit(0);
};
