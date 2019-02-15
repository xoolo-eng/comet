TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = ../../bin
LIBS += ../../../lib/libconfig.so
SOURCES += ../../src/test_config.cpp
INCLUDEPATH += ../../../include
