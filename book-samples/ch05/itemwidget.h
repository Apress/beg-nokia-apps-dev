#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QMainWindow>


namespace Ui {
    class ItemWidget;
}


class ItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ItemWidget(QWidget *parent = 0);

    void setData(const QString& data);

private:
    Ui::ItemWidget *ui;

};

#endif // ITEMWIDGET_H
