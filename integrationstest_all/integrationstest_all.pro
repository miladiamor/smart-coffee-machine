QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

CONFIG += c++17

INCLUDEPATH += $$PWD/../app/include

HEADERS += \
    ../app/include/kaffeeprogramm.h \
    ../app/include/ressourcen.h \
    ../app/include/koordinator.h \
    ../app/include/display.h \
    ../app/include/programmsteuerung.h \
    ../app/include/heizregler.h \
    ../app/include/heizelemente.h \
    ../app/include/pumpe.h \
    ../app/include/zuckerdispenser.h \
    ../app/include/bruehgruppe.h \
    ../app/include/klappe.h \
    ../app/include/ventil.h \
    ../app/include/motorsteuerung.h \
    ../app/include/zahlungseinheit.h \
    ../app/include/fuellstandmessung.h \
    ../app/include/kolbenmotor.h \
    ../app/include/inkrementalencoder.h \
    ../app/include/zahlungseinheit.h \
    ../app/include/muenzroehrenspeicher.h \
    ../app/include/muenzroehre.h \
    ../app/include/muenzschieber.h \
    ../app/include/muenzeingabesensor.h \
    ../app/include/muenzauswerfer.h \
    ../app/include/muenzschieber.h \

SOURCES +=  tst_tintegrationall.cpp \
    ../app/src/kaffeeprogramm.cpp \
    ../app/src/ressourcen.cpp \
    ../app/src/koordinator.cpp \
    ../app/src/display.cpp \
    ../app/src/programmsteuerung.cpp \
    ../app/src/bruehgruppe.cpp \
    ../app/src/motorsteuerung.cpp \
    ../app/src/zahlungseinheit.cpp \
    ../app/src/muenzroehrenspeicher.cpp
