/*
 * Chapter 3
 *
 * Demonstrates
 * - Use of worker thread for network access
 */

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "quakeevent.h"
#include <QMap>
#include <QThread>

#ifdef Q_OS_SYMBIAN
#include <QMobilityGlobal.h>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
QTM_USE_NAMESPACE
#endif

class QNetworkAccessManager;
class QNetworkReply;
class QuakeListModel;


class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject* owner, QuakeListModel& events);
    void run();

    void fetch(const QString& url);
    void cancel();

signals:
    void error(const QString& error);

private slots:
    void handleNetFinished(QNetworkReply* reply);

private:
    bool mCancelled;
    QNetworkAccessManager* mNetManager;
    QNetworkReply* mReply;
    QList<QString> mXmlTags;
    QuakeListModel& mEventModel;

#ifdef Q_OS_SYMBIAN
    QNetworkSession* mSession;
#endif
};

#endif // WORKERTHREAD_H
