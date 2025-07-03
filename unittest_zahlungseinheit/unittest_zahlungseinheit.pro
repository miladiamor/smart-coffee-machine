QT += testlib
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = tst_tzahlungseinheit

SOURCES += \
    tst_tzahlungseinheit.cpp \
    Zahlungseinheit.cpp \
    MuenzEingabeSensor.cpp \
    Produkt.cpp \
    Muenzroehrenspeicher.cpp \
    Muenzenschieber.cpp \
    Muenzroehre.cpp \
    MuenzAuswerfer.cpp

HEADERS += \
    Zahlungseinheit.h \
    MuenzEingabeSensor.h \
    Produkt.h \
    Muenzroehrenspeicher.h \
    Muenzenschieber.h \
    Muenzroehre.h \
    MuenzAuswerfer.h

INCLUDEPATH += ../
DEPENDPATH += ../
