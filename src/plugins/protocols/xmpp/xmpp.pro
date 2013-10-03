TEMPLATE = lib
CONFIG  += plugin
QT += core network widgets

LIBS += -lqxmpp -L../../../base/ -loxofrmbl_base

QMAKE_CXXFLAGS += -Wall -std=c++11

INCLUDEPATH += ../../../

TARGET = $$qtLibraryTarget(xmpp_plugin)

SOURCES += \
    XmppAccount.cpp \
    XmppContact.cpp \
    gui/XmppAccountWindow.cpp \
    XmppPlugin.cpp
    
HEADERS += \
    XmppContact.h \
    XmppAccount.h \
    gui/XmppAccountWindow.h \
    XmppPlugin.h
    
FORMS += gui/XmppAccountWindow.ui
