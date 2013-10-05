include(../../oxofrmbl.pri)


TEMPLATE = lib
QT += core network widgets

INCLUDEPATH += ../
QMAKE_CXXFLAGS += -Wall -std=c++11

TARGET = $$qtLibraryTarget(oxofrmbl_base)
DESTDIR = ../build/base

HEADERS += \
    ApplicationController.h \
    ChatMessage.h \
    Account.h \
    Contact.h \
    AccountManager.h \
    Person.h \
    ChatSession.h \
    Status.h \
    gui/StatusIcon.h

SOURCES += \
    ApplicationController.cpp \
    ChatSession.cpp \
    ChatMessage.cpp \
    Account.cpp \
    Contact.cpp \
    AccountManager.cpp \
    Status.cpp \
    gui/StatusIcon.cpp \
    Person.cpp

SOURCES += \
    gui/GuiController.cpp \
    gui/ContactList.cpp \
    gui/windows/ContactListWindow.cpp \
    gui/windows/ChatWindow.cpp \
    gui/windows/AccountsWindow.cpp \
    gui/widgets/ChatLogWidget.cpp \
    gui/widgets/ContactListWidget.cpp

HEADERS += \
    gui/GuiController.h \
    gui/ContactList.h \
    gui/windows/ContactListWindow.h \
    gui/windows/ChatWindow.h \
    gui/windows/AccountsWindow.h \
    gui/widgets/ChatLogWidget.h \
    gui/widgets/ContactListWidget.h \
    

FORMS += \
    gui/windows/ContactListWindow.ui \
    gui/windows/ChatWindow.ui \
    gui/windows/AccountsWindow.ui

target.path = $$LIBDIR/oxofrmbl/
INSTALLS += target
