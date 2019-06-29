TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cmd_line.cpp \
    test1.cpp

HEADERS += \
    ../../../../base/logs.h \
    ../../../../../base/logs.h \
    cmd_line.h \
    test1.h \
    stack_common.h \
    stack_data_races.h \
    stack_impl1.h \
    stack_impl2.h

QMAKE_LFLAGS += -pthread -lpthread

INCLUDEPATH += ../../../../../base

