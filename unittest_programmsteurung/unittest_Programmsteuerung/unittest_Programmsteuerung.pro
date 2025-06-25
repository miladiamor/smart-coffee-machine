QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/inlcude

SOURCES += \
        ../app/src/Programmsteuerung.cpp
        ../app/src/Pumpe.cpp
        ../app/src/Schaeumer.cpp
        tst_tprogrammsteuerung.cpp

HEADERS += \
../app/include/Programmsteuerung.h \
