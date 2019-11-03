TEMPLATE = app
CONFIG += console c++11 c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp


HEADERS += \
    ../../../base/logs.h \
    test1.h

QMAKE_LFLAGS += -pthread -lpthread
INCLUDEPATH += ../../../base

