/*
 * Chapter 3
 *
 * Demonstrates
 * - Use of worker thread for network access
 */

#include "workerthread.h"
#include "quakeevent.h"
#include "quakelistmodel.h"

#include <Qt>
#include <QtNetwork/QNetworkProxy>
#include <QXmlStreamReader>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrl>
#include <QMap>
#include <QList>
#include <QDebug>

WorkerThread::WorkerThread(QObject* owner, QuakeListModel& eventModel)
    : QThread(owner)
    , mCancelled(false)
    , mNetManager(0)
    , mReply(0)
    , mEventModel(eventModel)
{
    // Initialize the hashtable of tags we seek
    mXmlTags.append("id");
    mXmlTags.append("title");
    mXmlTags.append("updated");
    mXmlTags.append("summary");
    mXmlTags.append("point");
    mXmlTags.append("elev");
    mXmlTags.append("link");

    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager, SIGNAL(finished(QNetworkReply*)),
            this,        SLOT(handleNetFinished(QNetworkReply*)));
}


void WorkerThread::run()
{
    QuakeEvent anEvent;
    QXmlStreamReader xml;
    QXmlStreamReader::TokenType type;
    QString fieldName;
    QString value;
    QString tag;
    QMap<QString, QuakeEvent> events;
    bool successful = false;
    bool gotValue = false;
    bool gotEntry = false;

    xml.setDevice(mReply);
    while(!xml.atEnd())
    {
        // If we've been cancelled, stop processing.
        if (mCancelled) break;

        type = xml.readNext();
        QString tag = xml.name().toString().toLower();
        switch( type )
        {
            case QXmlStreamReader::StartElement:
                {
                    gotValue = false;
                    // Save aside the tag designation for efficiency's sake
                    if (tag == "entry") {
                        gotEntry = true;
                    } else if (mXmlTags.contains(tag)) {
                        fieldName = tag;
                        gotValue = false;
                    } else {
                        fieldName = QString();
                    }
                }
                break;
            case QXmlStreamReader::Characters:
                // Save aside any text
                if ( gotEntry && !fieldName.isEmpty() && !gotValue)
                {
                    value = xml.text().toString();
                    gotValue = true;
                }
                break;
            case QXmlStreamReader::EndElement:
                // Save aside this value
                if (gotValue && tag != "entry") {
                    anEvent.set(fieldName, value);
                } else if (tag == "entry"){
                    events.insert(anEvent.id(), anEvent);
                    anEvent.clear();
                    gotEntry = false;
                    gotValue = false;
                }
                break;
            default:
                break;
        }
    }

    successful = xml.hasError() ? false : true;

    if (!mCancelled && successful) {
        mEventModel.removeRows(0, mEventModel.rowCount());
        mEventModel.insertRows(0, events.count(), QModelIndex());
        int row = 0;
        // Convert the hash into a list
        foreach(anEvent, events) {
            mEventModel.setData(row++, anEvent);
        }
        mEventModel.setStatus(1);
        emit finished();
    } else if (!mCancelled) {
        emit error(tr("Could not interpret the server's response"));
        mEventModel.setStatus(3);
    }
}

void WorkerThread::fetch(const QString& url)
{
    // Don't try to re-start if we're running
    if (isRunning()) {
        this->cancel();
    }
    mEventModel.setStatus(2);
    // On Symbian, be sure we're using the desired access point.
    // MeeGo doesn't need this.
#ifdef Q_OS_SYMBIAN
    // Set Internet Access Point
    QNetworkConfigurationManager manager;


    const bool canStartIAP = (manager.capabilities()
                              & QNetworkConfigurationManager::CanStartAndStopInterfaces);


    // Is there default access point, use it
    QNetworkConfiguration cfg = manager.defaultConfiguration();
    if (!cfg.isValid() || (!canStartIAP && cfg.state() != QNetworkConfiguration::Active)) {
        emit error(tr("No Access Point found."));
        return;
    }

    mSession = new QNetworkSession(cfg, this);
    mSession->open();
    mSession->waitForOpened(-1);
#endif

    qDebug() << "About to fetch";

    // Data described at http://earthquake.usgs.gov/earthquakes/catalogs/
    // URL is one of http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml
    //              http://earthquake.usgs.gov/earthquakes/catalogs/7day-M2.5.xml
    //              http://earthquake.usgs.gov/earthquakes/catalogs/7day-M5.xml
    QNetworkReply *reply = mNetManager->get(QNetworkRequest(QUrl(url)));
    if (!reply) {
        emit error(tr("Could not contact the server"));
    }
}

void WorkerThread::cancel() {
    mCancelled = true;
    wait();
};

void WorkerThread::handleNetFinished(QNetworkReply* reply)
{
    // Start parse by starting.
    if (reply->error() == QNetworkReply::NoError) {
        if (!this->isRunning()) {
            mReply = reply;
            start();
        }
    } else {
        emit error(tr("A network error occurred"));
        qDebug() << QString("net error %1").arg(reply->error());
    }
}
