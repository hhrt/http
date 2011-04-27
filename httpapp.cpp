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

    TorrentsList torrentsList(root.get("result", "none").asString(), root.get("tag", "0").asUInt());

/*    std::cout << "Result: " << root.get("result", "none").asString() << "\n";
    std::cout << "Tag: " << root.get("tag", "0").asUInt() << "\n"; */

    Json::Value torrentsValue;
    torrentsValue = root["arguments"]["torrents"];
    Torrent *torrent;

    for(i=0;i<torrentsValue.size();i++) {
      torrent = new Torrent(torrentsValue[i]);
	  torrentsList.push_back(*torrent);
	  delete torrent;
    }

    std::cout << "Result: " << torrentsList.result() << "\n";
	std::cout << "Tag: " << torrentsList.tag() << "\n";
    std::cout << "Torrents list(" << torrentsList.size() <<"): \n";

    for(i=0;i<torrentsList.size();i++) {
	  std::cout << "ID: " << torrentsList[i].id() << " ";
	  std::cout << "Name: \"" << torrentsList[i].name() << "\" ";
	  std::cout << "Total_Size: " << torrentsList[i].size() << "\n";
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
