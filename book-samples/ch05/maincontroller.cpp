#include <QtGui>
#include <QMainWindow>
#include <QProgressDialog>
#include <QMessageBox>
#include <QListView>
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QAction>

#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>

#include "mapitemwidget.h"
#include "webactionproxy.h"
#include "maincontroller.h"
#include "quakeevent.h"
#include "workerthread.h"
#include "quakelistmodel.h"

// How often to get a new position
static int kLocationUpdateIntervalMs = 60000;

// Data URLs from USGS
static const char* k1DayUrl =
    "http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml";
static const char* k7DayUrl =
    "http://earthquake.usgs.gov/earthquakes/catalogs/7day-M2.5.xml";

// Javascript components for item view
static const char* kInitScript = "";
static const char* kExitItem =
    "<br/><br/><br/><p align=\"center\">"
    "<button type=\"button\" "
    "onclick=\"action.trigger()\">Back</button></p>";

// Not even worthy of being private methods
static qreal haversine(QPair<qreal, qreal> p,
                       QPair<qreal, qreal> q);
static qreal gcdDistance(QPair<qreal, qreal> p,
                        QPair<qreal, qreal> q);

enum {
    kListWidget = 0,
    kItemWidget,
    kMapWidget
};

MainController::MainController(QObject *parent)
    : QObject(parent)
    , mProgressDialog(0)
    , mBgThread(0)
    , mEventModel(new QuakeListModel())
    , mSortedModel(new QSortFilterProxyModel(this))
    , mListWidget(new QListView())
    , mItemWidget(new QWebView())
    , mMapWidget(new MapItemWidget())
    , mBackAction(0)
    , mShowListAction(0)
    , mShowMapAction(0)
    , mMainWidget(0)
    , mMainWindow(new QMainWindow)
    , mLocationSource(
            QGeoPositionInfoSource::createDefaultSource(this))
    , mLocationKnown(false)
    , mLocation(QPair<qreal,qreal>(0,0))
{
    createActions();

    mProgressDialog = new QProgressDialog(tr("Fetching data..."),
                                          tr("Cancel"),
                                          0, 0);

    mSortedModel->setSourceModel(mEventModel);
    mSortedModel->setDynamicSortFilter(false);
    mSortedModel->setSortRole(QuakeListModel::When);

    mListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mListWidget->setModel(mSortedModel);
    mListWidget->setContextMenuPolicy(Qt::NoContextMenu);

    mMapWidget->setModel(mSortedModel);

    connect(mListWidget, SIGNAL(clicked(QModelIndex)),
            this,        SLOT(handleItemClicked(QModelIndex)));

    addProxyObjects();
    mItemWidget->setContextMenuPolicy(Qt::NoContextMenu);
    connect(mItemWidget->page()->currentFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this,                                SLOT(addProxyObjects()));

    mMainWidget = new QStackedWidget(mMainWindow);
    mMainWidget->addWidget(mListWidget);
    mMainWidget->addWidget(mItemWidget);
    mMainWidget->addWidget(mMapWidget);
    mMainWidget->setCurrentIndex(kListWidget);
    mMainWidget->setContextMenuPolicy(Qt::NoContextMenu);
    mMainWindow->setCentralWidget(mMainWidget);

#if defined(Q_WS_S60)
    mMainWindow->showMaximized();
#else
    mMainWindow->show();
#endif

    if (mLocationSource) {
        connect(mLocationSource, SIGNAL(positionUpdated(const QGeoPositionInfo&)),
                this,            SLOT(positionUpdated(const QGeoPositionInfo&)));
        mLocationSource->setUpdateInterval(kLocationUpdateIntervalMs);
        mLocationSource->lastKnownPosition();
        mLocationSource->startUpdates();
    }

    QTimer::singleShot(0, this, SLOT(fetch()));
}

MainController::~MainController()
{
    if (mProgressDialog) delete mProgressDialog;
    if (mItemWidget) delete mItemWidget;
    if (mListWidget) delete mListWidget;
    if (mMapWidget) delete mMapWidget;
    if (mLocationSource) {
        mLocationSource->stopUpdates();
        delete mLocationSource;
    }
}

void MainController::createActions()
{
    mBackAction = new WebActionProxy( this );
    connect(mBackAction, SIGNAL(triggered()),
            this,        SLOT(handleItemClosed()));

    mShowListAction = new QAction(tr("Show List"), this);
    connect(mShowListAction, SIGNAL(triggered()),
            this,           SLOT(handleShowList()));

    mShowMapAction = new QAction(tr("Show Map"), this);
    connect(mShowMapAction, SIGNAL(triggered()),
            this,           SLOT(handleShowMap()));

    // Add to the options menu
    mMainWindow->menuBar()->addAction(mShowListAction);
    mMainWindow->menuBar()->addAction(mShowMapAction);
}

void MainController::fetch()
{
    fetch(k1DayUrl);
}

void MainController::fetch(const QString& url)
{
    if (mProgressDialog) mProgressDialog->show();
    if (!mBgThread)
        mBgThread = new WorkerThread(this, *mEventModel);
    connect(mBgThread, SIGNAL(finished()),
            this,      SLOT(handleRequestFinished()));
    connect(mBgThread, SIGNAL(error(const QString&)),
            this,      SLOT(handleError(const QString&)));
    mBgThread->fetch(url);
}

void MainController::handleRequestFinished() {
    if (mProgressDialog) mProgressDialog->hide();
    mMainWidget->setCurrentIndex(kListWidget);
    mSortedModel->sort(0, Qt::DescendingOrder);
}

void MainController::handleError(const QString& message)
{
    if (mProgressDialog) mProgressDialog->hide();
    QMessageBox box(QMessageBox::Critical,
                    QObject::tr("Error"),
                    message,
                    QMessageBox::Ok,
                    mMainWindow);
    qDebug() << message;
}

void MainController::handleItemClicked(const QModelIndex& which)
{
    QPair<qreal, qreal> where(mSortedModel->data(which, QuakeListModel::Latitude).value<qreal>(),
                              mSortedModel->data(which, QuakeListModel::Longitude).value<qreal>());
    QString distance = QString("unknown");
    QVariant desc = mSortedModel->data(which, QuakeListModel::Description);
    QVariant title = mSortedModel->data(which, QuakeListModel::DisplayRole);
    if (mLocationKnown) {
        distance = QString("%1 km (%2 mi)")
                   .arg((qreal)gcdDistance(where, mLocation))
                   .arg((qreal)gcdDistance(where, mLocation) / 1.609344);
    }

    QString html = QString("%1<h1>%2</h1>\n%3\n<strong>Distance</strong>: %4\n%5")
                   .arg(kInitScript)
                   .arg(title.value<QString>())
                   .arg(desc.value<QString>())
                   .arg(distance)
                   .arg(kExitItem);

    qDebug() << html;

    mItemWidget->setHtml(html);
    mMainWidget->setCurrentIndex(kItemWidget);
}

void MainController::handleItemClosed()
{
        mMainWidget->setCurrentIndex(kListWidget);
}

void MainController::handleLastDay()
{
    fetch(k1DayUrl);
}

void MainController::handleLastWeek()
{
    fetch(k7DayUrl);
}

void MainController::handleShowMap()
{
    mMainWidget->setCurrentIndex(kMapWidget);
}

void MainController::handleShowList()
{
    mMainWidget->setCurrentIndex(kListWidget);
}

void MainController::positionUpdated(const QGeoPositionInfo& update)
{
    if (update.isValid()) {
        QGeoCoordinate position = update.coordinate();
        mLocationKnown = true;
        mLocation = QPair<qreal, qreal>(position.latitude(),
                                        position.longitude());
    }
}

void MainController::addProxyObjects()
{
    mItemWidget->
            page()->
            currentFrame()->
            addToJavaScriptWindowObject("action",
                                        mBackAction,
                                        QScriptEngine::QtOwnership);
}

static const qreal kDegToRad = 0.0174532925;
static const qreal kEarthRadius = 6378.0;   // km

static qreal haversine(QPair<qreal, qreal> p,
                QPair<qreal, qreal> q) {
    qreal fromLat = p.first * kDegToRad;
    qreal fromLon = p.second * kDegToRad;
    qreal toLat = q.first * kDegToRad;
    qreal toLon = q.second * kDegToRad;

    qreal latitudeArc = (fromLat - toLat);
    qreal longitudeArc = (fromLon - toLon);
    qreal latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    qreal longitudeH = sin(longitudeArc * 0.5);
    longitudeH *= longitudeH;
    qreal tmp = cos(fromLat) * cos(toLat);

    return (2.0 * asin(sqrt(latitudeH + tmp * longitudeH)));
}

static qreal gcdDistance(QPair<qreal, qreal> p,
                         QPair<qreal, qreal> q)
{
    return haversine(p, q) * kEarthRadius;
}

