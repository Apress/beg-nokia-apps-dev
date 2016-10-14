/*
 * Chapter 3
 *
 * Demonstrates
 * - Use of Qt Creator for UI development
 */

#ifndef LISTFORM_H
#define LISTFORM_H
#include <QWidget>
#include "quakeevent.h"

class ListForm : public QWidget
{
    Q_OBJECT

public:
    ListForm(QWidget* parent = 0);
    ~ListForm();

public:
    void setModel(QAbstractItemModel& model);

private:
};

#endif /* LISTFORM_H */

