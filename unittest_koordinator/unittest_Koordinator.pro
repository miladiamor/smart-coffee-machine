QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES += tst_tkoordinator.cpp \
           ../app/src/Koordinator.cpp

HEADERS += ../app/include/Koordinator.h \
           ../app/include/Display.h \
           ../app/include/Programmsteuerung.h \
           ../app/include/Zahlungseinheit.h \
           ../app/include/Fuellstandsmessung.h \
           ../app/include/Kaffeeprogramm.h
