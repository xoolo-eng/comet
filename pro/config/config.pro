QT       -= core gui
CONFIG += c++14
TARGET = config
TEMPLATE = lib
DEFINES += SOCKET_LIBRARY
OBJECTS_DIR = ../../obj
DESTDIR = ../../lib
INCLUDEPATH += ../../include
SOURCES += \
        ../../src/comet/config.cpp
HEADERS += \
        ../../include/comet/config.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
