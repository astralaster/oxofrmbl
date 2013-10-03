#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT += core gui widgets network

TARGET = oxofrmbl
TEMPLATE = app

INCLUDEPATH += ./

SOURCES += main.cpp

HEADERS += \
    common.h \
    interfaces/PersonInterface.h \
    interfaces/ContactInterface.h \
    interfaces/AccountInterface.h \
    interfaces/PluginInterface.h \
    interfaces/ProtocolPluginInterface.h \

INCLUDES += QDebug

LIBS += -L./base/ -loxofrmbl_base

QMAKE_CXXFLAGS += -Wall -std=c++11
