QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_tprogrammsteuerung.cpp \
    ../app/src/Programmsteuerung.cpp

HEADERS += \
    ../app/include/Programmsteuerung.h \
    ../app/include/bruehgruppe.h \
    ../app/include/kaffeeprogramm.h \
    ../app/include/Pumpe.h \
    ../app/include/Zuckerdispenser.h \
    ../app/include/Schaeumer.h \
    ../app/include/Heizregler.h

