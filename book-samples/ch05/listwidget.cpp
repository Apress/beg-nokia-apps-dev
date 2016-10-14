#include <QtGui>
#include <QListView>

#include "listwidget.h"
#include "ui_listwidget.h"

ListWidget::ListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    connect(ui->listView, SIGNAL(clicked(QModelIndex)),
            this,           SLOT(itemClicked(QModelIndex)));
}

void ListWidget::setModel(QAbstractItemModel& model)
{
     ui->listView->setModel(&model);
}

void ListWidget::itemClicked(const QModelIndex& index)
{
    emit clicked(index);
}
