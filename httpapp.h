#ifndef HTTPAPP_H
#define HTTPAPP_H

#include<QCoreApplication>

class HttpApp : public QCoreApplication {

Q_OBJECT

  public:
  HttpApp(int argc, char *argv[]) : QCoreApplication(argc,argv) {}; 
  public slots:
  void getJsonData(QString jsonData);
  void closeApp(int errorCode);
};


#endif
