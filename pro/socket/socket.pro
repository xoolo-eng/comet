#-------------------------------------------------
#
# Project created by QtCreator 2019-02-15T13:56:24
#
#-------------------------------------------------

QT       -= core gui
CONFIG += c++14
TARGET = socket
TEMPLATE = lib
DEFINES += SOCKET_LIBRARY
OBJECTS_DIR = ../../obj
DESTDIR = ../../lib
INCLUDEPATH += ../../include
SOURCES += \
        ../../src/comet/socket.cpp
HEADERS += \
        ../../include/comet/socket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
