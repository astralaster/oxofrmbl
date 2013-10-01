#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = oxofrmbl
TEMPLATE = app

INCLUDEPATH += ./src

SOURCES += src/main.cpp\
    src/base/ChatMessage.cpp \
    src/base/ContactList.cpp \
    src/base/Account.cpp \
    src/base/Contact.cpp \
    src/base/AccountManager.cpp \
    src/plugins/protocols/xmpp/XmppContact.cpp \
    src/ApplicationController.cpp \
    src/plugins/protocols/xmpp/XmppAccount.cpp \
    src/gui/windows/ContactListWindow.cpp \
    src/gui/windows/ChatWindow.cpp \
    src/gui/windows/AccountsWindow.cpp \
    src/gui/widgets/ChatLogWidget.cpp \
    src/gui/widgets/ContactListWidget.cpp \
    src/gui/GuiController.cpp \
    src/base/ChatSession.cpp \
    src/plugins/protocols/xmpp/gui/XmppAccountWindow.cpp



HEADERS += src/common.h \
    src/base/ChatMessage.h \
    src/base/ContactList.h \
    src/base/Account.h \
    src/base/Contact.h \
    src/base/AccountManager.h \
    src/plugins/protocols/xmpp/XmppContact.h \
    src/ApplicationController.h \
    src/plugins/protocols/xmpp/XmppAccount.h \
    src/gui/windows/ContactListWindow.h \
    src/gui/windows/ChatWindow.h \
    src/gui/windows/AccountsWindow.h \
    src/gui/widgets/ChatLogWidget.h \
    src/gui/widgets/ContactListWidget.h \
    src/gui/GuiController.h \
    src/base/Person.h \
    src/base/ChatSession.h \
    src/plugins/protocols/xmpp/gui/XmppAccountWindow.h

FORMS += \
    src/gui/windows/ContactListWindow.ui \
    src/gui/windows/ChatWindow.ui \
    src/gui/windows/AccountsWindow.ui \
    src/plugins/protocols/xmpp/gui/XmppAccountWindow.ui

INCLUDES += QDebug

LIBS += -lqxmpp
QMAKE_CXXFLAGS += -Wall -std=c++11
