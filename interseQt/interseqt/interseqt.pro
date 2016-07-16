#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T21:25:49
#
#-------------------------------------------------

QT       -= gui

TARGET = interseqt
TEMPLATE = lib
CONFIG += staticlib

SOURCES += interseqt.cpp

HEADERS += interseqt.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
