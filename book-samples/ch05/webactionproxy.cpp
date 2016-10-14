#include "webactionproxy.h"

WebActionProxy::WebActionProxy(QObject *parent) :
    QObject(parent)
{
}

void WebActionProxy::trigger()
{
    emit triggered();
}
