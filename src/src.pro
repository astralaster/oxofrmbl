#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T12:05:32
#
#-------------------------------------------------

QT += core gui widgets network

TARGET = oxofrmbl
TEMPLATE = app

INCLUDEPATH += ./

SOURCES += \
    main.cpp \
    ApplicationController.cpp \
    gui/windows/ContactListWindow.cpp \
    gui/windows/ChatWindow.cpp \
    gui/windows/AccountsWindow.cpp \
    gui/widgets/ChatLogWidget.cpp \
    gui/widgets/ContactListWidget.cpp \
    gui/GuiController.cpp

HEADERS += \
    common.h \
    ApplicationController.h \
    gui/windows/ContactListWindow.h \
    gui/windows/ChatWindow.h \
    gui/windows/AccountsWindow.h \
    gui/widgets/ChatLogWidget.h \
    gui/widgets/ContactListWidget.h \
    gui/GuiController.h \
    interfaces/PersonInterface.h \
    interfaces/ContactInterface.h \
    AccountInterface.h

FORMS += \
    gui/windows/ContactListWindow.ui \
    gui/windows/ChatWindow.ui \
    gui/windows/AccountsWindow.ui

INCLUDES += QDebug

LIBS += -L./base/ -loxofrmbl_base

QMAKE_CXXFLAGS += -Wall -std=c++11
