#include<QCoreApplication>
#include<QDebug>
#include<iostream>
#include "httpposter.h"
#include "httpapp.h"
#include "json/json.h"

int main(int argc, char *argv[]) {

  bool debug = false;
  int i;

  HttpApp app(argc, argv);

  if(app.arguments().contains("debug")) {
	debug = true;
	qDebug() << "Debugging on.";
  }

  HttpPoster htr(debug);
  
  QObject::connect(&htr, SIGNAL(sendJsonData(QString)), &app, SLOT(getJsonData(QString)));
  QObject::connect(&htr, SIGNAL(httpPostError(int)), &app, SLOT(closeApp(int)));

  if(debug) qDebug() << "Setting connection parameters...";

  QString host = "127.0.0.1", port = "9091";
  if(app.arguments().contains("-h")) {
    host = app.arguments()[app.arguments().indexOf("-h")+1];	
  }
  if(app.arguments().contains("-p")) {
	port = app.arguments()[app.arguments().indexOf("-p")+1];
  }

  if(debug) qDebug() << "host: " << host << " port: " << port;

  if(htr.setConnectionSettings(host, port)) {
    if(debug) qDebug() << "Start requesting...";
    htr.sendRequest();
    return app.exec();
  }
  else
	return 1;
  

}
