#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T12:50:53
#
#-------------------------------------------------

QT       += network
include(../QAliOSS.pri)
QT       -= gui

TARGET = QAliOSS
TEMPLATE = lib

DEFINES += QALIOSS_LIBRARY

SOURCES += qalioss.cpp \
    utl.cpp

HEADERS += qalioss.h\
        QAliOSS_global.h \
    utl.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE072D924
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = QAliOSS.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
