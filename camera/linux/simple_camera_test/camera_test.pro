TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tests.cpp \
    test_types.cpp \
    videodev1.cpp \
    videodev2.cpp

HEADERS += \
    tests.h \
    test_types.h \
    videodev1.h \
    videodev2.h
