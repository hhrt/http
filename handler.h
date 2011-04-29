#ifndef HANDLER_H
#define HANDLER_H
#include<QObject>

class QStringList;
class TransmRpcSession;

class Handler : public QObject {

Q_OBJECT

  public:
  Handler(QStringList args);
  public slots:
  void errorHandler(int errorCode);
  void successHandler();

  private:
  TransmRpcSession *session;

};


#endif
