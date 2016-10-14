#include "mapitemwidget.h"
#include "quakelistmodel.h"

#include <QPainter>
#include <math.h>

MapItemWidget::MapItemWidget(QWidget *parent)
    : QWidget(parent)
    , mMap(QPixmap())
    , mMapSize(0,0)
    , mModel(0)
{
}

MapItemWidget::~MapItemWidget()
{
}

void MapItemWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the base map
    QPoint pt;
    pt.setX(size().width() /2 - mMap.size().width() /2);
    pt.setY(size().height()/2 - mMap.size().height()/2);
    painter.drawPixmap(pt, mMap);

    // Draw the markers
    painter.setBrush(Qt::SolidPattern);
    for( int i = mMarkers.length(); i>0; i--)
    {
        QPair<QPoint, int> marker = mMarkers.at(i-1);

        pt = marker.first;
        int r = marker.second;
        painter.fillRect(pt.x()-r, pt.y()-r, 2*r, 2*r, QColor(255, 0, 0));
    }
}

void MapItemWidget::resizeEvent(QResizeEvent *event)
{
    if (size() != mMapSize) {
        initMap();
        initMarkers();
    }
}

void MapItemWidget::setModel(QAbstractItemModel* model)
{
    if (mModel) {
        disconnect(mModel, 0, this, 0);
    }
    mModel = model;
    if (mModel) {
        connect(mModel, SIGNAL(columnsMoved(QModelIndex&, int, int, QModelIndex&, int )),
                this,   SLOT(itemsMoved(QModelIndex,int,int,QModelIndex,int)));
        connect(mModel, SIGNAL(rowsMoved(QModelIndex&, int, int, QModelIndex&, int )),
                this,   SLOT(itemsMoved(QModelIndex,int,int,QModelIndex,int)));
        connect(mModel, SIGNAL(columsRemoved(QModelIndex&, int, int)),
                this,   SLOT(itemsRemoved(QModelIndex,int,int)));
        connect(mModel, SIGNAL(rowsRemoved(QModelIndex&, int, int)),
                this,   SLOT(itemsRemoved(QModelIndex,int,int)));
        connect(mModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this,   SLOT(itemsChanged(QModelIndex,QModelIndex)));
        connect(mModel, SIGNAL(modelReset()),
                this,   SLOT(itemsReset()));
    }
}

void MapItemWidget::itemsMoved(const QModelIndex&, int, int, const QModelIndex&, int)
{
    initMarkers();
    update();
}

void MapItemWidget::itemsRemoved(const QModelIndex&, int, int)
{
    initMarkers();
    update();
}

void MapItemWidget::itemsChanged(const QModelIndex&, const QModelIndex &)
{
    initMarkers();
    update();
}

void MapItemWidget::itemsReset()
{
    initMarkers();
    update();
}

void MapItemWidget::initMap()
{
    // Load the map bitmap
    QPixmap map(":/images/map.jpg");

    // Minimally scale the map image to fit the width and height,
    // preserving aspect ratio.
    qreal ratiox = static_cast<qreal>(size().width())/static_cast<qreal>(map.size().width());
    qreal ratioy = static_cast<qreal>(size().height())/static_cast<qreal>(map.size().height());
    qreal scale = qMin(ratiox, ratioy);

    QSize newSize(map.size().width()  * scale,
                  map.size().height() * scale);

    if (newSize!=map.size()) {
        mMap = map.scaled(newSize, Qt::KeepAspectRatio);
    }
    // Record the widget size so we only rescale when we need to
    mMapSize = size();
}

static const qreal kDegToRad = 0.0174532925;
static const qreal kPiOver4  = 0.785398164;
// From wikipedia, http://en.wikipedia.org/wiki/Mercator_projection
QPoint MapItemWidget::geoToWidgetCoords(qreal lat, qreal lon)
{
    // First, convert to ideal planar coordinates on
    // the plane (-1, -1, 1, 1)
    qreal sinlat = sin(lat*kDegToRad);
    qreal x = lon/180;
    qreal y = log((1+sinlat)/(1-sinlat))/4;

    // Then scale the coordinates for the current map
    qreal scalex = static_cast<qreal>(mMap.size().width())/2;
    qreal scaley = static_cast<qreal>(mMap.size().height())/2;

    x *= scalex;
    y *= scaley;
    x += mMap.size().width() / 2;
    y = mMap.size().height() / 2 - y;

    // And finally, translate the coordinates to the widget coordinates
    QPoint result(x, y);
    QPoint offset((size().width()  - mMap.size().width() ) / 2,
                  (size().height() - mMap.size().height()) / 2);
    return result + offset;
}

void MapItemWidget::initMarkers()
{
    // Always start from scratch
    mMarkers.clear();

    if (!mModel) {
        return;
    }

    for(int i = 0;  i < mModel->rowCount(); i++)
    {
        QModelIndex index = mModel->index(i, 0);
        qreal lat = mModel->data(index, QuakeListModel::Latitude).value<qreal>();
        qreal lon = mModel->data(index, QuakeListModel::Longitude).value<qreal>();
        qreal mag = mModel->data(index, QuakeListModel::Magnitude).value<qreal>();
        QPoint point = geoToWidgetCoords(lat, lon);
        mMarkers.append(QPair<QPoint, int>(point, mag));
    }
}

