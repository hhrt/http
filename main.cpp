#include<QCoreApplication>
#include<QDebug>
#include<iostream>
#include "httpposter.h"
#include "httpapp.h"

int main(int argc, char *argv[]) {

  bool debug = false;
  HttpApp app(argc, argv);
  
  if(app.arguments().contains("debug")) debug = true;

  HttpPoster htr(debug);

  QObject::connect(&htr, SIGNAL(sendJsonData(QString)), &app, SLOT(getJsonData(QString)));
  QObject::connect(&htr, SIGNAL(httpPostError(int)), &app, SLOT(closeApp(int)));

  if(debug) qDebug() << "Setting connection settings...";
  if(htr.setConnectionSettings()) {
    if(debug) qDebug() << "Start requesting...";
    htr.sendRequest();
    return app.exec();
  }
  else
	return 1;
  

}
