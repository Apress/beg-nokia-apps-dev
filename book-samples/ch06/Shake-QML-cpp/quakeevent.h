/*
 * Chapter 3
 *
 * Demonstrates
 * - Container class for earthquake events
 */

#ifndef QUAKEEVENT_H
#define QUAKEEVENT_H

#include <QString>
#include <QDateTime>
#include <QMap>
#include <QPair>
#include <QMetaType>

class QuakeEvent : public QObject {
    Q_OBJECT

public:
    QuakeEvent(QObject* parent = 0);
    QuakeEvent(const QuakeEvent& other);
    QuakeEvent& operator=(const QuakeEvent&);

    QString id() const;
    QString summary() const;
    QDateTime when() const;
    QString where() const;
    qreal magnitude() const;
    QPair<qreal, qreal> position() const;
    qreal elevation() const;
    QString html() const;

    // Used to determine distance from the user
    qreal distanceTo(QPair<qreal, qreal> geocoord) const;

    // Used by the XML parser
    void set(const QString& name, const QString& value);
    QString get(const QString& name) const;

    bool isEmpty() const;
    void clear();

    // For use when sorting by time
    bool operator<(const QuakeEvent& b) const;

private:
    qreal haversine(QPair<qreal, qreal> geocoord) const;
    QMap<QString, QString> mData;
    static bool mRegisterMetaType;
};

#endif // QUAKEEVENT_H
