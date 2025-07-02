QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_ti_programmsteuerung_bruehgruppe.cpp \
    ../app/src/bruehgruppe.cpp \
    ../app/src/programmsteuerung.cpp

HEADERS += ../app/include/bruehgruppe.h \
    ../app/include/programmsteuerung.h
