QT += core
QT -= gui

CONFIG += c++11

TARGET = interseqt-cli
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../interseqt/release/ -linterseqt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../interseqt/debug/ -linterseqt
else:unix: LIBS += -L$$OUT_PWD/../interseqt/ -linterseqt

INCLUDEPATH += $$PWD/../interseqt
DEPENDPATH += $$PWD/../interseqt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../interseqt/release/libinterseqt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../interseqt/debug/libinterseqt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../interseqt/release/interseqt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../interseqt/debug/interseqt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../interseqt/libinterseqt.a
