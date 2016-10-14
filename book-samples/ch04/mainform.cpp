/*
 * Chapter 3
 *
 * Demonstrates
 * - Use of Qt Creator for UI development
 */

#include <QtGui>
#include <QMessageBox>
#include <QListView>
#include <QWebView>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QBoxLayout>

#include "mainform.h"
#include "quakeevent.h"
#include "workerthread.h"
#include "quakelistmodel.h"

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , mBgThread(0)
    , mEventModel(new QuakeListModel())
    , mSortedModel(new QSortFilterProxyModel(this))
    , mListView(new QListView(this))
    , mItemView(new QWebView(this))
    , mMainView(new QWidget(this))
{
    mItemView->setHtml(tr("<body><p align=\"center\">Loading data... please wait</p></body>"));

    mSortedModel->setSourceModel(mEventModel);
    mSortedModel->setDynamicSortFilter(false);
    mSortedModel->setSortRole(QuakeListModel::When);
    mListView->setModel(mSortedModel);

    mListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QBoxLayout::Direction direction;
    if (height()>=width()) {
        direction = QBoxLayout::LeftToRight;
    } else {
        direction = QBoxLayout::TopToBottom;
    }
    QBoxLayout *layout = new QBoxLayout(direction, mMainView);

    layout->addWidget(mListView, 1);
    layout->addWidget(mItemView, 1);
    mMainView->setLayout(layout);

    setCentralWidget(mMainView);

    connect(mListView, SIGNAL(clicked(QModelIndex)),
            this,      SLOT(handleItemClicked(QModelIndex)));

    QTimer::singleShot(0, this, SLOT(fetch()));
}

MainForm::~MainForm() {
}

void MainForm::fetch()
{
    // TODO derive URL from top menu's selected item
    // TODO start distraction graphic

    // Data described at http://earthquake.usgs.gov/earthquakes/catalogs/
    // URL is one of http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml
    //               http://earthquake.usgs.gov/earthquakes/catalogs/7day-M2.5.xml
    //               http://earthquake.usgs.gov/earthquakes/catalogs/7day-M5.xml
    if (!mBgThread)
        mBgThread = new WorkerThread(this, *mEventModel);
    connect(mBgThread, SIGNAL(finished()),
            this,      SLOT(handleRequestFinished()));
    connect(mBgThread, SIGNAL(error(const QString&)),
            this,      SLOT(handleError(const QString&)));
    mBgThread->fetch("http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml");
    // TODO Start distraction graphic
}

void MainForm::handleRequestFinished() {
    // TODO Stop distraction graphic
    mSortedModel->sort(0, Qt::DescendingOrder);
    mItemView->setHtml(tr("<body><p align=\"center\">Select an item for more details.</p></body>"));
}

void MainForm::handleError(const QString& message)
{
    // TODO stop distraction graphic
    QMessageBox box(QMessageBox::Critical,
                    QObject::tr("Error"),
                    message,
                    QMessageBox::Ok,
                    this);
    qDebug() << message;
}

void MainForm::handleItemClicked(const QModelIndex& which)
{
    QVariant html = mSortedModel->data(which, QuakeListModel::Description);
    qDebug() << html.value<QString>();
    mItemView->setHtml(html.value<QString>());
}

