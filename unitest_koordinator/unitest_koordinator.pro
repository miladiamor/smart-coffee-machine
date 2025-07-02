QT += testlib gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES += \
    tst_koordinator.cpp \
    ../app/src/koordinator.cpp

HEADERS += \
    ../app/include/koordinator.h
