TEMPLATE = app
CONFIG += console c++11 c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../common/move_only_class.cpp \
    test1.cpp


HEADERS += \
    ../../../../base/logs.h \
    ../../common/move_only_class.h \
    test1.h

QMAKE_LFLAGS += -pthread -lpthread
INCLUDEPATH += ../../../../base
INCLUDEPATH += ../../common
