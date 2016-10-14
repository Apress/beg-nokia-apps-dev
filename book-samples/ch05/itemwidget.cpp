#include <QtGui>
#include <QWebView>

#include "itemwidget.h"
#include "ui_itemwidget.h"


ItemWidget::ItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ItemWidget)
{
    ui->setupUi(this);
}

void ItemWidget::setData(const QString &data)
{
    ui->itemView->setHtml(data);
}

