#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include "handler.h"

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  Handler handler(app.arguments());

  return app.exec();
}
