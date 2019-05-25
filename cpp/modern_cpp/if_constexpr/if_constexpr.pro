TEMPLATE = app
CONFIG += console c++11 c++17 -std=c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp

HEADERS += \
    test1.h \
    ../../../base/logs.h

INCLUDEPATH += ../../../base


