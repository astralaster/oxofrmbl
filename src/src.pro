include(../oxofrmbl.pri)

#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT += core gui widgets network

TARGET = oxofrmbl
DESTDIR = build
TEMPLATE = app

INCLUDEPATH += ./
QMAKE_CXXFLAGS += -Wall -std=c++11

HEADERS += \
    common.h \
    interfaces/PluginInterface.h \
    interfaces/ProtocolPluginInterface.h

SOURCES += main.cpp

target.path = $$PREFIX/bin/
INSTALLS += target


CONFIG(debug, debug|release) {
    LIBS += -L./build/base -loxofrmbl_base
} else {
    LIBS += -Wl,-rpath,/usr/lib/oxofrmbl -L./build/base -loxofrmbl_base
}
