QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES += \
    tst_tst_fuellstandsmessung.cpp\
    ../app/src/Fuellstandsmessung.cpp \
    ../app/src/Tankwaage.cpp \
    ../app/src/Ressourcen.cpp

HEADERS += \
    ../app/include/Fuellstandsmessung.h \
    ../app/include/Tankwaage.h \
    ../app/include/Ressourcen.h
