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
    src/Fuellstandsmessung.cpp \
    src/Heizelemente.cpp \
    src/Heizregler.cpp \
    src/Koordinator.cpp \
    src/MuenzEingabeSensor.cpp \
    src/MuenzAuswerfer.cpp \
    src/Muenzenschieber.cpp \
    src/Muenzroehre.cpp \
    src/Muenzroehrenspeicher.cpp \
    #src/Produkt.cpp \
    src/Programmsteuerung.cpp \
    src/Pumpe.cpp \
    src/Ressourcen.cpp \
    src/Schaeumer.cpp \
    src/Tankwaage.cpp \
    src/Temperatursensor.cpp \
    #src/Zahlungseinheit.cpp \
    src/Zuckerdispenser.cpp \
    src/bruehgruppe.cpp \
    src/clock.cpp \
    src/display.cpp \
    src/inkrementalencoder.cpp \
    src/kaffeeprogramm.cpp \
    src/klappe.cpp \
    src/kolbenmotor.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/motorsteuerung.cpp \
    #src/muenze.cpp \
    src/simulation.cpp \
    src/ventil.cpp

# The header files (e.g. *.h)
HEADERS += \
    include/Zahlungseinheit.h \
    include/ausgabeeinheit.h \
    include/bruehgruppe.h \
    include/clock.h \
    include/display.h \
    include/Fuellstandsmessung.h \
    include/Heizelemente.h \
    include/Heizregler.h \
    include/inkrementalencoder.h \
    include/kaffeeprogramm.h \
    include/klappe.h \
    include/kolbenmotor.h \
    include/Koordinator.h \
    include/mainwindow.h \
    include/motorsteuerung.h \
    include/Muenzenschieber.h \
    include/muenzroehre.h \
    include/muenzroehrenspeicher.h \
    include/MuenzEingabeSensor.h \
    include/MuenzAuswerfer.h \
    #include/produkt.h \
    include/Programmsteuerung.h \
    include/Pumpe.h \
    include/Ressourcen.h \
    include/Rezept.h \
    include/Schaeumer.h \
    include/simulation.h \
    include/Tankwaage.h \
    include/Temperatursensor.h \
    include/ventil.h \
    include/Zuckerdispenser.h

# The GUI definition files (so-called forms)
FORMS += \
    mainwindow.ui

# Resources to integrate (e.g. images)
RESOURCES += \
    data/data.qrc

# Other files to include in the distribution
DISTFILES += \
    default.cfg
