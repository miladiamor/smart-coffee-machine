QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tmotorsteuerung.cpp \
        ../app/src/motorsteuerung.cpp

HEADERS += ../app/include/motorsteuerung.h \
        ../app/include/bruehgruppe.g \
        ../app/include/kolbenmotor.h \
        ../app/include/inkrementalencoder.h
