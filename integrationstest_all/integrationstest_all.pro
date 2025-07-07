QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

CONFIG += c++17

INCLUDEPATH += $$PWD/../app/include

HEADERS += \
    ../app/include/koordinator.h \
    ../app/include/display.h \
    ../app/include/programmsteuerung.h \
    ../app/include/heizregler.h \
    ../app/include/bruehgruppe.h \
    ../app/include/motorsteuerung.h \
    ../app/include/zahlungseinheit.h \
    ../app/include/fuellstandmessung.h \


SOURCES +=  tst_tintegrationall.cpp \
    ../app/src/koordinator.cpp \
    ../app/src/display.cpp \
    ../app/src/programmsteuerung.cpp \
    ../app/src/heizregler.cpp \
    ../app/src/bruehgruppe.cpp \
    ../app/src/motorsteuerung.cpp
