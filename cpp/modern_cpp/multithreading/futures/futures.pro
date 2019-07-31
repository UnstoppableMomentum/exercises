TEMPLATE = app
CONFIG += console c++11 c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test1.cpp \
    test2.cpp \
    test3.cpp \
    ../../common/move_only_class.cpp

HEADERS += \
    test1.h \
    ../../../../base/logs.h \
    test2.h \
    test3.h \
    ../../common/move_only_class.h

QMAKE_LFLAGS += -pthread -lpthread
INCLUDEPATH += ../../../../base
INCLUDEPATH += ../../common
