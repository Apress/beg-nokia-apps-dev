QT      +=  webkit network
HEADERS =   mainwindow.h
SOURCES =   main.cpp \
            mainwindow.cpp
#RESOURCES = jquery.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/webkit/fancybrowser
#fix this later
target.path = c:\book\hybridshell
#sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro
#sources.path = $$[QT_INSTALL_EXAMPLES]/webkit/fancybrowser
INSTALLS += target

debug { MMP_RULES -= "PAGED" MMP_RULES += "UNPAGED" }

symbian {
    stuff.sources = hworld.html
    stuff.path = /web
    DEPLOYMENT += stuff
    TARGET.UID3 = 0xA000CF6C
    include(symbianpkgrules.pri)
    CONFIG += mobility
    MOBILITY += bearer
    TARGET.CAPABILITY += NetworkServices ReadUserData
}
linux-g++ {
    stuff.sources = main.cpp
    stuff.path = /usr/local/share/shake/web
    INSTALLS += stuff
}

OTHER_FILES += \
    hybridshell.desktop

unix:!symbian {
    desktopfile.files = $${TARGET}.desktop
    maemo5 {
        desktopfile.path = /usr/share/applications/hildon
    } else {
        desktopfile.path = /usr/share/applications
    }
    INSTALLS += desktopfile
}

RESOURCES +=

OTHER_FILES +=

RESOURCES +=

OTHER_FILES +=

RESOURCES +=

RESOURCES += \
    hybridshellqrc.qrc

unix:!symbian {
    desktopfile.files = $${TARGET}.desktop
    maemo5 {
        desktopfile.path = /usr/share/applications/hildon
    } else {
        desktopfile.path = /usr/share/applications
    }
    INSTALLS += desktopfile
}

OTHER_FILES += \
    index.html

OTHER_FILES += \
    RSSReader.css

OTHER_FILES += \
    RSSReader.js

OTHER_FILES += \
    FeedUpdateBroker.js
