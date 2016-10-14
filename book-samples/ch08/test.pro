#-------------------------------------------------
#
# Project created by QtCreator 2010-09-06T13:17:54
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_quakeevent
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../quake

SOURCES += tst_quakeevent.cpp \
    ../../Quake/quakeevent.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
