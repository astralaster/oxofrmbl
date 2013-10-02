TEMPLATE = lib
QT += core network widgets

QMAKE_CXXFLAGS += -Wall -std=c++11

INCLUDEPATH += ../

TARGET = $$qtLibraryTarget(oxofrmbl_base)

HEADERS += \
    ChatMessage.h \
    ContactList.h \
    Account.h \
    Contact.h \
    AccountManager.h \
    Person.h \
    ChatSession.h

SOURCES += \
    ChatSession.cpp \
    ChatMessage.cpp \
    ContactList.cpp \
    Account.cpp \
    Contact.cpp \
    AccountManager.cpp