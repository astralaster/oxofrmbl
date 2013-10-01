#include "Account.h"

#include <QDebug>

Account::Account(QObject *parent) : Person(parent)
{
}

Account::~Account()
{
}


ChatSession *Account::getSession(const QString &contactId)
{
    return chatSessions.contains(contactId) ? chatSessions[contactId] : nullptr;
}

QMap<QString, ChatSession*> Account::getSessions()
{
    return chatSessions;
}

QList<Contact*> Account::getContacts()
{
    return contacts;
}

bool Account::isActive() const
{
    return active;
}

void Account::addContact(Contact *contact)
{
    contacts.append(contact);
}

ChatSession *Account::startSession(Contact *contact)
{
    ChatSession *session;

    if(!chatSessions.contains(contact->getId())) {
        session = new ChatSession(contact, this);

        chatSessions[contact->getId()] = session;

        emit sessionStarted(session);
    } else {
        session = chatSessions[contact->getId()];
        emit sessionActivated(session);
    }

    return session;
}

void Account::endSession(ChatSession *session)
{
    chatSessions.remove(session->getContact()->getId());
    delete session;
}