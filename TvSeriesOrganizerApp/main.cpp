#include <QtGui/QGuiApplication>
#include "controller/controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Controller c;
    c.run();

    return app.exec();
}