#ifndef WEBACTIONPROXY_H
#define WEBACTIONPROXY_H

#include <QObject>

class WebActionProxy : public QObject
{
    Q_OBJECT

public:
    explicit WebActionProxy(QObject *parent = 0);

public slots:
    void trigger();

signals:
    void triggered();
};

#endif // WEBACTIONPROXY_H
