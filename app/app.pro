QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Using C++17 standard
CONFIG += c++17

# Your custom version info
VERSION = 0.1

# Directories for builds
DESTDIR = dist
OBJECTS_DIR = build
UI_DIR = gen/ui
MOC_DIR = gen/moc
RCC_DIR = gen/rcc

# disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Directories that are searched when including header files, no need for explicit directories, e.g. #include "../../code/foo.h" in source files
INCLUDEPATH += $$PWD/include

# The source files (e.g. *.cpp)
SOURCES += \
    src/display.cpp \
    src/kaffeeprogramm.cpp \
    src/mainwindow.cpp \
    src/Pumpe.cpp \
    src/Koordinator.cpp \
    src/Temperatursensor.cpp \
    src/Tankwaage.cpp \
    src/Fuellstandsmessung.cpp \
    src/Programmsteuerung.cpp \
    src/Ressourcen.cpp \
    src/bruehgruppe.cpp \
    src/clock.cpp \
    src/inkrementalencoder.cpp \
    src/klappe.cpp \
    src/kolbenmotor.cpp \
    src/simulation.cpp \
    src/ventil.cpp \
    src/main.cpp \
    src/Heizregler.cpp \
    src/Heizelemente.cpp \
    src/Schaeumer.cpp \
    src/Zuckerdispenser.cpp \
    src/Programmsteuerung.cpp \
    src/Muenzenschieber.cpp
    src/motorsteuerung.cpp \

# The header files (e.g. *.h)
HEADERS += \
    include/display.h \
    include/Pumpe.h \
    include/Koordinator.h \
    include/Tankwaage.h \
    include/Fuellstandsmessung.h \
    include/Heizelemente.h \
    include/Heizregler.h \
    include/Programmsteuerung.h \
    include/Ressourcen.h \
    include/Rezept.h \
    include/Schaeumer.h \
    include/Temperatursensor.h \
    include/Zuckerdispenser.h \
    include/ausgabeeinheit.h \
    include/bruehgruppe.h \
    include/geldschein.h \
    include/geldscheinbehaelter.h \
    include/geldscheinsensor.h \
    include/inkrementalencoder.h \
    include/klappe.h \
    include/kolbenmotor.h \
    include/motorsteuerung.h \
    include/muenze.h \
    include/muenzroehre.h \
    include/muenzroehrenspeicher.h \
    include/muenzsensor.h \
    include/produkt.h \
    include/ventil.h \
    include/zahlungseinheit.h \
    include/clock.h \
    include/simulation.h \
    include/kaffeeprogramm.h \
    include/mainwindow.h \
    include/Muenzenschieber.h


# The GUI definition files (so-called forms)
FORMS += \
    mainwindow.ui

# Resources to integrate (e.g. images)
RESOURCES += \
    data/data.qrc

# Other files to include in the distribution
DISTFILES += \
    default.cfg
