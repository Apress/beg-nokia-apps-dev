#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include <QPair>
#include <QMobilityGlobal.h>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>

class QSortFilterProxyModel;
class QProgressDialog;
class QModelIndex;
class QAction;
class QMainWindow;
class QStackedWidget;
class QListView;
class QWebView;
class WebActionProxy;
class WorkerThread;
class QuakeListModel;
class MapItemWidget;

QTM_USE_NAMESPACE

class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject *parent = 0);
    ~MainController();

    void fetch(const QString& url);

public slots:
    void fetch();
    void handleRequestFinished();
    void handleError(const QString& message);
    void handleItemClicked(const QModelIndex&);
    void handleItemClosed();
    void handleLastDay();
    void handleLastWeek();
    void handleShowMap();
    void handleShowList();
    void positionUpdated(const QGeoPositionInfo&);
    void addProxyObjects();

private:
    void createActions();

    QProgressDialog *mProgressDialog;

    WorkerThread* mBgThread;
    QuakeListModel* mEventModel;
    QSortFilterProxyModel* mSortedModel;

    QListView* mListWidget;
    QWebView* mItemWidget;
    MapItemWidget* mMapWidget;

    WebActionProxy* mBackAction;
    QAction* mShowListAction;
    QAction* mShowMapAction;

    QStackedWidget* mMainWidget;
    QMainWindow* mMainWindow;

    QGeoPositionInfoSource* mLocationSource;
    bool mLocationKnown;
    QPair<qreal,qreal> mLocation;
};

#endif // MAINCONTROLLER_H
