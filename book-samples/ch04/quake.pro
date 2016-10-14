# Chapter 3
# XML parser text tool
# Demonstrates
# - Use of Qt Designer and Qt Creator
# - QObject, signals & slots
# - Network programming
# - XML parsing
CONFIG += uitools \
    debug_and_release \
    warn_on
QT += network webkit

HEADERS = mainform.h \
    workerthread.h \
    quakeevent.h \
    quakelistmodel.h
SOURCES = main.cpp \
    mainform.cpp \
    workerthread.cpp \
    quakeevent.cpp \
    quakelistmodel.cpp

TRANSLATIONS = quakeform_en.ts
CODECFORTR = UTF-8

symbian {
    TARGET.CAPABILITY = NetworkServices  ReadUserData
    CONFIG += mobility
    MOBILITY += bearer
    # TODO ICON = icon.svg
    # TODO get valid UID3
}
