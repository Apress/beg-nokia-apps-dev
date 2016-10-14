#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QMainWindow>

namespace Ui {
    class ListWidget;
}

class QModelIndex;
class QAbstractItemModel;

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = 0);

    void setModel(QAbstractItemModel&);

signals:
    void clicked(const QModelIndex& index);

public slots:
    void itemClicked(const QModelIndex& index);

private:
    Ui::ListWidget *ui;
};

#endif // LISTWIDGET_H
