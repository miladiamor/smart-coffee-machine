QT += testlib core
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = tst_tzahlungseinheit

SOURCES += \
    tst_tzahlungseinheit.cpp \
    ../app/src/Zahlungseinheit.cpp \




HEADERS += ../app/include/Zahlungseinheit.h \
           ../app/include/MuenzEingabeSensor.h \
           ../app/include/Produkt.h \
           ../app/include/Muenzroehrenspeicher.h \
           ../app/include/Muenzenschieber.h \
           ../app/include/Muenzroehre.h \
           ../app/include/MuenzAuswerfer.h





INCLUDEPATH += $$PWD/../app/include
DEPENDPATH += ../
