TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp \
    test2.cpp \
    test3.cpp

HEADERS += \
    test1.h \
    ../../../../base/logs.h \
    test2.h \
    test3.h

QMAKE_LFLAGS += -pthread -lpthread


INCLUDEPATH += ../../../../base


