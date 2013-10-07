include(../../../../oxofrmbl.pri)

TEMPLATE = lib
CONFIG  += plugin
QT += core network widgets

INCLUDEPATH += ../../../
QMAKE_CXXFLAGS += -Wall -std=c++11

TARGET = $$qtLibraryTarget(xmpp_plugin)
DESTDIR = ../../../build/plugins/protocols/xmpp/

LIBS += -lqxmpp

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

target.path = $$LIBDIR/oxofrmbl/plugins/protocols/xmpp/

INSTALLS += target

CONFIG(debug, debug|release) {
    LIBS += -L../../../build/base -loxofrmbl_base
} else {
    LIBS += -Wl,-rpath,/usr/lib/oxofrmbl -L../../../build/base -loxofrmbl_base
}
