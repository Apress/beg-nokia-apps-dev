/*
 * Chapter 3
 *
 * Demonstrates
 * - Use of Qt Creator for UI development
 */

#ifndef QUAKEFORM_H
#define QUAKEFORM_H
#include <QList>
#include <QMainWindow>
#include "quakeevent.h"


class WorkerThread;
class QuakeListModel;
class QSortFilterProxyModel;
class QModelIndex;
class QListView;
class QWebView;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = 0);
    ~MainForm();

public slots:
    void fetch();

private slots:
    void handleRequestFinished();
    void handleError(const QString& message);
    void handleItemClicked(const QModelIndex&);

private:
    WorkerThread* mBgThread;
    QuakeListModel* mEventModel;
    QSortFilterProxyModel* mSortedModel;
    QListView* mListView;
    QWebView* mItemView;
    QWidget* mMainView;
};

#endif /* QUAKEFORM_H */

