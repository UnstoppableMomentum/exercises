TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp \
    test2.cpp \
    test3.cpp
HEADERS += \
    ../../../../base/logs.h \
    test1.h \
    test2.h \
    test3.h
