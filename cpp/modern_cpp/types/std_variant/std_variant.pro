TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp \
    test2.cpp

HEADERS += \
    test1.h \
    ../../../../base/logs.h \
    test2.h

INCLUDEPATH += ../../../../base

QMAKE_CXXFLAGS += -std=gnu++17
