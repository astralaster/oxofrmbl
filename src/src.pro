#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT += core gui widgets network

TARGET = oxofrmbl
TEMPLATE = app

INCLUDEPATH += ./

HEADERS += \
    common.h \
    interfaces/PluginInterface.h \
    interfaces/ProtocolPluginInterface.h

SOURCES += main.cpp

INCLUDES += QDebug

LIBS += -L./base/ -loxofrmbl_base

QMAKE_CXXFLAGS += -Wall -std=c++11
