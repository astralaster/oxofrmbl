#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = xmpp
TEMPLATE = app

INCLUDEPATH += ./src ./src/base

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/base/ChatClient.cpp \
    src/base/ChatMessage.cpp \
    src/plugins/protocols/xmpp/SimpleXmppClient.cpp \
    src/base/ChatContact.cpp \
    src/plugins/protocols/xmpp/XmppContact.cpp


HEADERS += src/mainwindow.h \
    src/base/ChatClient.h \
    src/base/ChatMessage.h \
    src/plugins/protocols/xmpp/SimpleXmppClient.h \
    src/base/ChatContact.h \
    src/plugins/protocols/xmpp/XmppContact.h

FORMS += src/mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/qxmpp/release/ -lqxmpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/qxmpp/debug/ -lqxmpp
else:unix: LIBS += -L$$PWD/lib/qxmpp/ -lqxmpp

INCLUDEPATH += $$PWD/lib/qxmpp/client $$PWD/lib/qxmpp/base
DEPENDPATH += $$PWD/lib/qxmpp/client $$PWD/lib/qxmpp/base
