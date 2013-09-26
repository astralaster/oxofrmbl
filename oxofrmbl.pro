#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = oxofrmbl
TEMPLATE = app

INCLUDEPATH += ./src ./src/base

SOURCES += src/main.cpp\
    src/base/ChatMessage.cpp \
    src/plugins/protocols/xmpp/XmppContact.cpp \
    src/base/ContactList.cpp \
    src/gui/ContactListWindow.cpp \
    src/base/Account.cpp \
    src/base/Contact.cpp \
    src/base/AccountManager.cpp \
    src/plugins/protocols/xmpp/XmppAccount.cpp \
    src/gui/ChatWindow.cpp \
    src/gui/ChatLogWidget.cpp \
    src/ApplicationController.cpp


HEADERS += \
    src/base/ChatMessage.h \
    src/plugins/protocols/xmpp/XmppContact.h \
    src/base/ContactList.h \
    src/gui/ContactListWindow.h \
    src/base/Account.h \
    src/base/Contact.h \
    src/base/AccountManager.h \
    src/plugins/protocols/xmpp/XmppAccount.h \
    src/gui/ChatWindow.h \
    src/gui/ChatLogWidget.h \
    src/ApplicationController.h

FORMS += \
    src/gui/ContactListWindow.ui \
    src/gui/ChatWindow.ui

LIBS += -lqxmpp
QMAKE_CXXFLAGS += -Wall -std=c++11
