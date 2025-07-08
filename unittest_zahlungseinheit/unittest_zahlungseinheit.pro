QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES += \
    tst_tzahlungseinheit.cpp \
    ../app/src/Zahlungseinheit.cpp \


HEADERS += \
    ../app/include/Zahlungseinheit.h \
    ../app/include/MuenzEingabeSensor.h \
    ../app/include/Muenzroehrenspeicher.h \
    ../app/include/MuenzAuswerfer.h \
    ../app/include/Display.h

