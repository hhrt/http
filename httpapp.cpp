#include "httpapp.h"
#include<iostream>
#include<QCoreApplication>
#include<QDebug>

#include "errorcodes.h"

void HttpApp::getJsonData(QString jsonData) {

  std::cout << ">>> " << jsonData.toAscii().data();
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
