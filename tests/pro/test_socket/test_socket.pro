TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = ../../bin
LIBS += ../../../lib/libsocket.so
SOURCES += ../../src/test_socket.cpp
INCLUDEPATH += ../../../include
