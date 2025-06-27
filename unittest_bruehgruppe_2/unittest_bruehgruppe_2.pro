QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_tbruehgruppe.cpp \
    ../app/src/bruehgruppe.cpp \

HEADERS += \
    ../app/include/bruehgruppe.h \
    ../app/include/klappe.h \
    ../app/include/motorsteuerung.h \
    ../app/include/ventil.h \
    ../app/include/kaffeeprogramm.h
