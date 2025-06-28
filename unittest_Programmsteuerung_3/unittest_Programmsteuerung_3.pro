QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES +=  tst_tprogrammsteuerung.cpp \
    ../app/src/Programmsteuerung.cpp \
    ../app/src/bruehgruppe.cpp \
    ../app/src/kaffeeprogramm.cpp \
    ../app/src/Pumpe.cpp \
    ../app/src/Zuckerdispenser.cpp \
    ../app/src/Schaeumer.cpp \
    ../app/src/Heizelemente.cpp \
    ../app/src/Heizregler.cpp \
    ../app/src/ventil.cpp \
    ../app/src/klappe.cpp


HEADERS += \
    ../app/include/Programmsteuerung.h \
    ../app/include/bruehgruppe.h \
    ../app/include/kaffeeprogramm.h \
    ../app/include/Pumpe.h \
    ../app/include/Zuckerdispenser.h \
    ../app/include/Schaeumer.h \
    ../app/include/Heizelemente.h \
    ../app/include/Heizregler.h \
    ../app/include/klappe.h \
    ../app/include/ventil.h
