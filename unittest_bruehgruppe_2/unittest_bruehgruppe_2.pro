QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_tbruehgruppe.cpp \
    ../app/src/motorsteuerung.cpp \
    ../app/src/kaffeeprogramm.cpp \
    ../app/src/bruehgruppe.cpp \
    ../app/src/inkrementalencoder.cpp \
    ../app/src/klappe.cpp \
    ../app/src/kolbenmotor.cpp \
    ../app/src/ventil.cpp

HEADERS += \
    ../app/include/bruehgruppe.h \
    ../app/include/inkrementalencoder.h \
    ../app/include/klappe.h \
    ../app/include/kolbenmotor.h \
    ../app/include/motorsteuerung.h \
    ../app/include/ventil.h \
    ../app/include/kaffeeprogramm.h
