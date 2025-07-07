QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_koordinator_integration.cpp \
    ../app/src/Koordinator.cpp \
    ../app/src/fuellstandsmessung.cpp \
    ../app/src/display.cpp\
    ../app/src/Ressourcen.cpp \
    ../app/src/Tankwaage.cpp

HEADERS += ../app/include/Display.h \
    ../app/include/Koordinator.h \
    ../app/include/Programmsteuerung.h \
    ../app/include/Fuellstandsmessung.h \
    ../app/include/Zahlungseinheit.h \
    ../app/include/Ressourcen.h \
    ../app/include/Tankwaage.h \
    ../app/include/Kaffeeprogramm.h
