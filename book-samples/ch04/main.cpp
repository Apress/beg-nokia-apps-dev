/*
 * Chapter 3
 *
 * Demonstrates
 * - Application startup
 */

#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QtNetwork/QNetworkProxy>

#include "mainform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#if 0
    // Network proxy
    // Remove before providing code to Apress!
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("172.19.89.59");
    proxy.setPort(8080);
    QNetworkProxy::setApplicationProxy(proxy);
    // End things to remove
#endif

    // Configure localization
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("quake") + locale);
    app.installTranslator(&translator);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    // Bring up our main form
    MainForm form;
    app.setActiveWindow(&form);
    form.showNormal();

    // Start the application
    return app.exec();
}
