QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++17

TEMPLATE = app

INCLUDEPATH += $$PWD/../app/include

SOURCES += \
        ../app/src/Programmsteuerung.cpp\
        ../app/src/Pumpe.cpp\
        ../app/src/Schaeumer.cpp\
        ../app/src/Zuckerdispenser.cpp\
        ../app/src/Temperatursensor.cpp\
        ../app/src/kaffeeprogramm.cpp\
        ../app/src/Heizregler.cpp\
        ../app/src/Heizelemente.cpp\
        tst_tprogrammsteuerung.cpp

HEADERS += \
        ../app/include/Programmsteuerung.h
        ../app/include/Pumpe.h\
        ../app/include/Schaeumer.h\
        ../app/include/Zuckerdispenser.h\
        ../app/include/Temperatursensor.h\
        ../app/include/kaffeeprogramm.h\
        ../app/include/Heizregler.h\
        ../app/include/Heizelemente.h\
        tst_tprogrammsteuerung.h

