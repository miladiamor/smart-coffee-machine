QT += testlib gui core

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++17

TEMPLATE = app

SOURCES += tst_tkoordinator.cpp

# If you place MockKoordinator in a separate .cpp, add it here:
# SOURCES += MockKoordinator.cpp

# No HEADERS needed unless you separate into .h/.cpp
