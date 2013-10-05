#include "Account.h"

#include "Status.h"
#include "ChatMessage.h"
#include "Contact.h"
#include "ChatSession.h"

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

/*QString Account::getId() const
{
    if(accountId.isEmpty()) {
        return account->getId();
    } else {
        return accountId;
    }
}*/

QString Account::getDisplayName() const
{
    if(nickname.isEmpty()) {
        return getDisplayName();
    } else {
        return nickname;
    }
}

Status *Account::getStatus()
{
    return status;
}

void Account::setId(const QString &id)
{
    accountId = id;
}

bool Account::isConnected() const
{
    return connectedStatus;
}

bool Account::isActive() const
{
    return active;
}

void Account::contactStatusChangedSlot(Status *status)
{
    emit contactStatusChanged(qobject_cast<Contact*>(QObject::sender()), status);
}

void Account::addContact(Contact *contact)
{
    contacts.append(contact);
    connect(contact, &Contact::statusChanged, this, &Account::contactStatusChangedSlot);
}

void Account::setStatus(Status *status)
{
    Person::setStatus(status);
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
