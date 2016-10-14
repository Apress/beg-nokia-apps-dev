#include <QtGui/QApplication>
#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainController* controller = new MainController;
    int result = app.exec();
    delete controller;
    return result;
}
