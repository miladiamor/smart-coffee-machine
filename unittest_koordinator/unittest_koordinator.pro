QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++17

TEMPLATE = app
QT += core gui

# Add your app include folder
INCLUDEPATH += $$PWD/../app/include

# Sources to compile
SOURCES += \
    tst_tst_koordinator.cpp \
    ../app/src/Koordinator.cpp \
    ../app/src/Programmsteuerung.cpp \
    ../app/src/kaffeeprogramm.cpp \
    ../app/src/Zahlungseinheit.cpp \
    ../app/src/display.cpp

# Headers (for navigation, optional but recommended)
HEADERS += \
    ../app/include/Koordinator.h \
    ../app/include/Programmsteuerung.h \
    ../app/include/kaffeeprogramm.h \
    ../app/include/Zahlungseinheit.h \
    ../app/include/display.h
