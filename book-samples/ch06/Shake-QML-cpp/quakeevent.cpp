/*
 * Chapter 3
 *
 * Demonstrates
 * - Container class for earthquake events
 */
#include "quakeevent.h"
#include <QString>
#include <QStringList>
#include <QDateTime>
#include "math.h"

static const qreal kDegToRad = 0.0174532925; 
static const qreal kEarthRadius = 6378.0;   // km

QuakeEvent::QuakeEvent(QObject* parent) : QObject(parent)
{
}

QuakeEvent::QuakeEvent(const QuakeEvent& other)
{
    *this = other;
}

QuakeEvent& QuakeEvent::operator=(const QuakeEvent& other)
{
    this->set("id", other.get("id"));
    this->set("title", other.get("title"));
    this->set("summary", other.get("summary"));
    this->set("point", other.get("point"));
    this->set("elev", other.get("elev"));
    return *this;
}

QString QuakeEvent::summary() const {
    return mData.value("title");
}


QString QuakeEvent::id() const {
    return mData.value("id");
}

qreal QuakeEvent::magnitude() const
{
    QString title = mData.value("title");
    // Format of title is "M 2.6, Baja California, Mexico"
    QString mag = title.mid(2, 3);
    return mag.toFloat();
}

QString QuakeEvent::where() const
{
    QString title = mData.value("title");
    // Format of title is "M 2.6, Baja California, Mexico"
    QString where = title.mid(title.indexOf(", ")+2);
    return where;
}

QPair<qreal, qreal> QuakeEvent::position() const
{
    // Stored in point; format is "59.9533 -151.4761"
    QString position = mData.value("point");
    QString lat = position.mid(0, position.indexOf(" "));
    QString lon = position.mid(position.indexOf(" ")+1);
    return QPair<qreal, qreal>(lat.toFloat(), lon.toFloat());
}

qreal QuakeEvent::elevation() const
{
    QString elevation = mData.value("elev");
    return elevation.toFloat();
}


QDateTime QuakeEvent::when() const {
    // Parse the HTML because there's no absolute time in the feed
    const char* months[] = {"January", "February", "March",
                            "April", "May", "June",
                            "July", "August", "September",
                            "October", "November", "December" };
    QString html = get("summary");
    if (html.isEmpty()) return QDateTime();
    int month = -1, day = -1, year = -1;
    int hour = -1, minute = -1, second = -1;
    int cursor = -1;
    // date/time is in the form "Monday, May  3, 2010 13:38:18 UTC"
    for(int i = 0; i < 12; i++) {
        cursor = html.indexOf(months[i]);
        if (cursor>-1) {
            month = i+1;
            cursor += QString(months[i]).length();
            break;
        }
    }
    bool isWhitespace = true;
    QChar c;
    do {
        c = html[cursor++];
        if (c.isDigit()) {
            day = c.digitValue();
            isWhitespace = false;
        }
    } while(isWhitespace);
    c = html[cursor++];
    if (c.isDigit()) {
        day = day * 10 + c.digitValue();
        cursor++;
    }
    // Skip ", " between day and year
    cursor+=1;
    year = html.mid(cursor, 4).toInt();
    // Skip year and single space after year
    cursor+=5;
    // Now get hours, minutes, and seconds
    QStringList time = html.mid(cursor, 8).split(":");
    hour = time[0].toInt();
    minute = time[1].toInt();
    second = time[2].toInt();
    return QDateTime(QDate(year, month, day), QTime(hour, minute, second, 0), Qt::UTC);
}

qreal QuakeEvent::distanceTo(QPair<qreal, qreal> geocoord) const {
    return haversine(geocoord) * kEarthRadius;
}

bool QuakeEvent::operator<(const QuakeEvent& b) const {
    return this->when() < b.when();
}

void QuakeEvent::set(const QString& name, const QString& value) {
    mData.insert(name, value);
}

QString QuakeEvent::get(const QString& name) const {
    return mData.value(name);
}

bool QuakeEvent::isEmpty() const {
    return mData.size() == 0;
}

void QuakeEvent::clear() {
    mData.clear();
}

QString QuakeEvent::html() const {
    return mData.value("summary");
}

qreal QuakeEvent::haversine(QPair<qreal, qreal> p) const {
    qreal fromLat = this->position().first * kDegToRad;
    qreal fromLon = this->position().second * kDegToRad;
    qreal toLat = p.first * kDegToRad;
    qreal toLon = p.second * kDegToRad;

    qreal latitudeArc = (fromLat - toLat);
    qreal longitudeArc = (fromLon - toLon);
    qreal latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    qreal longitudeH = sin(longitudeArc * 0.5);
    longitudeH *= longitudeH;
    qreal tmp = cos(fromLat) * cos(toLat);

    return (2.0 * asin(sqrt(latitudeH + tmp * longitudeH)));
}
