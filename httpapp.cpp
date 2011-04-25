#include "httpapp.h"
#include<iostream>
#include<QCoreApplication>
#include<QDebug>
#include "json/json.h"

#include "errorcodes.h"

HttpApp::HttpApp(int &argc, char *argv[]) : QCoreApplication(argc, argv) {
};

void HttpApp::getJsonData(QString jsonData) {

  Json::Value root;
  Json::Reader reader;

  if(!reader.parse(jsonData.toAscii().data(), root)) 
	std::cout << "Error parsing json data!\n";

  QString requestResult(root.get("result", "none").asString().c_str());
  int resultTag(root.get("tag", "none").asInt());

  std::cout << "Result: " << requestResult.toAscii().data() << "\n";
  std::cout << "Tag: " << resultTag << "\n";

  Json::Value torrents;
  torrents = root["arguments"]["torrents"];

  std::cout << "Torrents list(" << torrents.size() <<"): \n";

  int i;
  for(i=0;i<torrents.size();i++) {
  
    std::cout << "ID: " << torrents[i].get("id", "0").asInt() << " ";
	std::cout << "Name: \"" << torrents[i].get("name", "none").asString() << "\" ";
	std::cout << "Total size: " << torrents[i].get("totalSize", "0").asInt() << "\n";

  }

  exit(0);

};

void HttpApp::closeApp(int errorCode) {
  switch(errorCode) {
    case fileOpenError:
      qDebug() << "Error Code: " << errorCode << " File open error!";
	break;
	case connectionError:
	  qDebug() << "Error Code: " << errorCode << "Connection error!";
	break;
	case dataRecievingError:
	  qDebug() << "Error Code: " << errorCode << "Data recieving error!";
	break;
	default:
	  qDebug() << "Error Code: " << errorCode << "Unknown error!";
  }

  exit(errorCode);
}
