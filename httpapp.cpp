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
  try {
    Json::Value root;
    Json::Reader reader;
    unsigned int i;

    if(!reader.parse(jsonData.toAscii().data(), root)) 
	  std::cout << "Error parsing json data!\n";

    Json::Value torrentsValue;
    torrentsValue = root["arguments"]["torrents"];
    Torrent *torrent;
	TorrentsList torrentsList;

	*torrentsList.result() = root.get("result", "none").asString();
	*torrentsList.tag() = root.get("tag", "0").asUInt();

    for(i=0;i<torrentsValue.size();i++) {
      torrent = new Torrent(torrentsValue[i]);
	  torrentsList.torrents()->push_back(*torrent);
	  delete torrent;
    }

    std::cout << "Result: " << *torrentsList.result() << "\n";
	std::cout << "Tag: " << *torrentsList.tag() << "\n";
    std::cout << "Torrents list(" << torrentsList.torrents()->size() <<"): \n";

    for(i=0;i<torrentsList.torrents()->size();i++) {
	  std::cout << "ID: " << *(torrentsList.torrents()->at(i).id()) << " ";
	  std::cout << "Name: \"" << *(torrentsList.torrents()->at(i).name()) << "\" ";
	  std::cout << "Total_Size: " << std::fixed << (long unsigned int)*(torrentsList.torrents()->at(i).size()) << "Bytes\n";
    }
  }
  catch(std::exception &e) {
	qDebug() << "\nError: " << e.what() << "\n";
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
