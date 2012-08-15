#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T12:51:19
#
#-------------------------------------------------

QT       += network testlib
include(../QAliOSS.pri)
LIBS+=-lQAliOSS
QT       -= gui

TARGET = tst_tstqaliosstest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tstqaliosstest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
