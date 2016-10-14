#-------------------------------------------------
#
# Project created by QtCreator 2010-08-06T21:27:37
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = quake
TEMPLATE = app

SOURCES += main.cpp \
    quakeevent.cpp \
    quakelistmodel.cpp \
    workerthread.cpp \
    maincontroller.cpp \
    webactionproxy.cpp \
    mapitemwidget.cpp

HEADERS  += quakeevent.h \
    quakelistmodel.h \
    workerthread.h \
    maincontroller.h \ 
    webactionproxy.h \
    mapitemwidget.h

CONFIG += mobility
MOBILITY += location

symbian {
    TARGET.UID3 = 0xe58833d1
    TARGET.CAPABILITY = NetworkServices  ReadUserData WriteUserData UserEnvironment LocalServices ReadDeviceData WriteDeviceData Location
    CONFIG += mobility
    MOBILITY += bearer

    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    resources.qrc
