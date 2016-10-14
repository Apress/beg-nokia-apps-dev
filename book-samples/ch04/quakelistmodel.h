/*
 * Chapter 3
 *
 * Demonstrates
 * - Model for UI elements
 */

#ifndef QUAKELISTMODEL_H
#define QUAKELISTMODEL_H

#include <QStandardItemModel>
#include <QObject>
#include <QList>
#include "quakeevent.h"

class QuakeListModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QuakeListModel(QObject* parent = 0)
        : QStandardItemModel(parent) {}

    enum {
        DisplayRole = Qt::DisplayRole,          // returns summary()
        DecorationRole = Qt::DecorationRole,    // returns QPixmap map()
        Id = Qt::UserRole + 1,                  // returns id();
        When,                                   // returns QDateTime when() const;
        WhereText,                              // returns  QString where() const;
        Magnitude,                              // returns qreal magnitude() const;
        WhereCoordinates,                       // returns QPair(QPair<qreal, qreal> position() const, qreal elevation() const;)
        Description                             // html() returns HTML full summary
    };

    bool setData(int row, const QuakeEvent& value);
};

#endif // QUAKELISTMODEL_H
