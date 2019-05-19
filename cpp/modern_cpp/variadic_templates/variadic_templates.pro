TEMPLATE = app
CONFIG += console c++11 c++17 -std=c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp \
    test2.cpp
HEADERS += \
    ../../../base/logs.h \
    test1.h \
    test2.h
