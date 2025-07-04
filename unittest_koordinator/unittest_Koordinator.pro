QT += core gui testlib

CONFIG += console
CONFIG -= app_bundle


TEMPLATE = testlib

INCLUDEPATH += $$PWD/../app/include

SOURCES += tst_tkoordinator.cpp \
           ../app/src/Koordinator.cpp

HEADERS += ../app/include/Koordinator.h \
           ../app/include/Display.h \
           ../app/include/Programmsteuerung.h \
           ../app/include/Zahlungseinheit.h \
           ../app/include/Fuellstandsmessung.h \
           ../app/include/Kaffeeprogramm.h
