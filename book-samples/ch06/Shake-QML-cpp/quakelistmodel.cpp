#include "quakelistmodel.h"
#include <QStandardItem>
#include <QHash>
#include <QPair>
#include <QList>

QuakeListModel::QuakeListModel(QObject* parent)
    : QStandardItemModel(parent) {
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "title";
    roles[QuakeListModel::Description] = "summary";
    setRoleNames(roles);
}

bool QuakeListModel::setData(int row,
                             const QuakeEvent& value)
{
    if (row < rowCount()) {
        QStandardItem* item = new QStandardItem();

        item->setData(QVariant(value.id()), QuakeListModel::Id);
        item->setData(QVariant(value.summary()), QuakeListModel::DisplayRole);
        item->setData(QVariant(value.when()), QuakeListModel::When);
        item->setData(QVariant(value.where()), QuakeListModel::WhereText);
        item->setData(QVariant(value.html()), QuakeListModel::Description);
        QStringList coord;
        coord << QString("%1").arg(value.position().first);
        coord << QString("%1").arg(value.position().second);
        coord << QString("%1").arg(value.elevation());
        item->setData(coord, QuakeListModel::WhereCoordinates);
        item->setData(value.position().first, QuakeListModel::Latitude);
        item->setData(value.position().second, QuakeListModel::Longitude);
        item->setData(QVariant(value.magnitude()), QuakeListModel::Magnitude);

        setItem(row, 0, item);

        return true;
    }
    return false;
}

int QuakeListModel::status()
{
    return mStatus;
}

void QuakeListModel::setStatus(int status){
    mStatus = status;
    emit statusChanged();
}

/* Roles for quake data
Qt::DisplayRole QString summary() const;
QuakeListModel::Id QString id() const;
QuakeListModel::When QDateTime when() const;
QuakeListModel::WhereText QString where() const;
QuakeListModel::Magnitude qreal magnitude() const;
QuakeListModel::GeoPosition QPair(QPair<qreal, qreal> position() const, qreal elevation() const;)
QuakeListModel::Description html()
*/
