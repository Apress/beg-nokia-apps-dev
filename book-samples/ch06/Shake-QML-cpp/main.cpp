#include <QMetaType>
#include <QtGui/QApplication>
#include <QMainWindow>
#include <QModelIndex>
#include <QDeclarativeView>
#include <QDeclarativeContext>

#include "quakelistmodel.h"
#include "workerthread.h"

#include "qmlapplicationviewer.h"

static const char* kUrl =
    "http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml";

int main(int argc, char *argv[])
{
    qRegisterMetaType<QModelIndex>("QModelIndex");

    QApplication app(argc, argv);

    QMainWindow window(0);
    QuakeListModel* model = new QuakeListModel(&window);
    WorkerThread* worker = new WorkerThread(&window, *model);
    worker->fetch(kUrl);

    QDeclarativeView view;

    // The only thing we show is the declarative view.
    window.setCentralWidget(&view);
    window.showMaximized();


    // Proxy in our app controller so QML and JavaScript can
    // get its properties and show our QML
    view.rootContext()->setContextProperty("feedModel", model);

    view.setSource(QUrl("qml/Shake-QML/main.qml"));

    return app.exec();
}
