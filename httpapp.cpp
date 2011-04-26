#include "httpapp.h"
#include<iostream>
#include <vector>
#include<QCoreApplication>
#include<QDebug>
#include "json/json.h"

#include "errorcodes.h"
#include "torrent.h"

HttpApp::HttpApp(int &argc, char *argv[]) : QCoreApplication(argc, argv) {
};

void HttpApp::getJsonData(QString jsonData) {

  Json::Value root;
  Json::Reader reader;

  if(!reader.parse(jsonData.toAscii().data(), root)) 
	std::cout << "Error parsing json data!\n";

  std::cout << "Result: " << root.get("result", "none").asString() << "\n";
  std::cout << "Tag: " << root.get("tag", "0").asUInt() << "\n";

  Json::Value torrentsValue;
  torrentsValue = root["arguments"]["torrents"];
  Torrent *torrent;

  std::vector<Torrent> torrents;

  unsigned int i;

  try {
    for(i=0;i<torrentsValue.size();i++) {
     /* torrent.set_id(torrentsValue[i].get("id", "0").asUInt());
	  torrent.set_size(torrentsValue[i].get("totalSize", "0").asDouble());
	  torrent.set_name(torrentsValue[i].get("name", "none").asString()); */

      torrent = new Torrent(torrentsValue[i]);

	  torrents.push_back(*torrent);

	  delete torrent;
    }
  }
  catch(std::exception &e) {
    std::cout << "\nError: " << e.what() << "\n";	
  }

  std::cout << "Torrents list(" << torrents.size() <<"): \n";

  for(i=0;i<torrents.size();i++) {
	std::cout << "ID: " << torrents[i].id() << " ";
	std::cout << "Name: \"" << torrents[i].name() << "\" ";
	std::cout << "Total_Size: " << torrents[i].size() << "\n";
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
