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
    include/bruehgruppe.cpp \
    include/inkrementalencoder.cpp \
    include/klappe.cpp \
    include/kolbenmotor.cpp \
    include/ventil.cpp \
    src/main.cpp

# The header files (e.g. *.h)
HEADERS += \
    include/bruehgruppe.h \
    include/inkrementalencoder.h \
    include/klappe.h \
    include/kolbenmotor.h \
    include/ventil.h

# The GUI definition files (so-called forms)
FORMS += \
    mainwindow.ui

# Resources to integrate (e.g. images)
RESOURCES += \
    data/data.qrc

# Other files to include in the distribution
DISTFILES += \
    default.cfg
