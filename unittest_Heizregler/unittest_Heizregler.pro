QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_theizregler.cpp \
        ../app/src/Heizregler.cpp


HEADERS += ../app/include/Heizregler.h \
           ../app/include/Heizelemente.h \
           ../app/include/Temperatursensor.h
