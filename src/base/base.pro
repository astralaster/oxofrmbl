include(../../oxofrmbl.pri)

TEMPLATE = lib
QT += core network widgets

INCLUDEPATH += ../
QMAKE_CXXFLAGS += -Wall -std=c++11

TARGET = $$qtLibraryTarget(oxofrmbl_base)
DESTDIR = ../build/base

#LIBS += -lotr

CONFIG += precompile_header
PRECOMPILED_HEADER  = ../common.h

HEADERS += \
    ApplicationController.h \
    ChatMessage.h \
    Account.h \
    Contact.h \
    AccountManager.h \
    Person.h \
    ChatSession.h \
    Status.h \
    gui/StatusIcon.h \
    #otr/OtrMessageHandler.h \
    gui/windows/AddContactDialog.h \
    gui/windows/TabbedChatWindow.h \
    FileTransfer.h \
    gui/windows/FileTransfersDialog.h \
    gui/AccountList.h

SOURCES += \
    ApplicationController.cpp \
    ChatSession.cpp \
    ChatMessage.cpp \
    Account.cpp \
    Contact.cpp \
    AccountManager.cpp \
    Status.cpp \
    gui/StatusIcon.cpp \
    Person.cpp \
    #otr/OtrMessageHandler.cpp \
    gui/windows/AddContactDialog.cpp \
    gui/windows/TabbedChatWindow.cpp \
    FileTransfer.cpp \
    gui/windows/FileTransfersDialog.cpp \
    gui/AccountList.cpp

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
    gui/windows/AccountsWindow.ui \
    gui/windows/AddContactDialog.ui \
    gui/windows/TabbedChatWindow.ui \
    gui/windows/FileTransfersDialog.ui

CONFIG(debug, debug|release) {
    DEFINES += 'OXOFRMBL_LIBDIR=\"QCoreApplication::applicationDirPath()\"'
} else {
    DEFINES += 'OXOFRMBL_LIBDIR=\'\"$${OXOFRMBL_LIBDIR}\"\''
}

target.path = $$LIBDIR/oxofrmbl/
INSTALLS += target
