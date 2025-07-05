QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_tmotorsteuerung.cpp \
        ../app/src/motorsteuerung.cpp

HEADERS += ../app/include/motorsteuerung.h \
        ../app/include/bruehgruppe.h \
        ../app/include/kolbenmotor.h \
        ../app/include/inkrementalencoder.h
