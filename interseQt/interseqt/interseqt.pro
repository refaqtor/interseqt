#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T21:25:49
#
#-------------------------------------------------

QT       -= gui

TARGET = interseqt
TEMPLATE = lib
CONFIG += staticlib

SOURCES += interseqt.cpp \
    mapfile.cpp \
    processconnection.cpp \
    versioncontrolsystem.cpp

HEADERS += interseqt.h \
    mapfile.h \
    processconnection.h \
    versioncontrolsystem.h
unix {
    target.path = /usr/libR
    INSTALLS += target
}
