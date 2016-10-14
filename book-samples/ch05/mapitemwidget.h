#ifndef MAPITEMWIDGET_H
#define MAPITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QModelIndex>
#include <QList>

class QAbstractItemModel;

class MapItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapItemWidget(QWidget *parent = 0);
    ~MapItemWidget();

    void setModel(QAbstractItemModel* model);

signals:

public slots:

    void itemsMoved(const QModelIndex& sourceParent, int sourceStart, int sourceEnd, const QModelIndex& destinationParent, int destinationColumn);
    void itemsRemoved(const QModelIndex& parent, int start, int end );
    void itemsChanged(const QModelIndex& topLeft, const QModelIndex & bottomRight );
    void itemsReset();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void initMap();
    void initMarkers();

    QPoint geoToWidgetCoords(qreal lat, qreal lon);

    QPixmap mMap;
    QSize mMapSize;

    QList<QPair<QPoint, int> > mMarkers;
    QAbstractItemModel* mModel;
};

#endif // MAPITEMWIDGET_H
