#include "Account.h"

#include <QDebug>

Account::Account(AccountInterface *account, QObject *parent) : Person(parent)
{
    setAccountObject(account);
}

Account::~Account()
{
}

void Account::initAccount()
{
    account->initAccount();
}

AccountInterface *Account::getAccountObject()
{
    return account;
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

QString Account::getType() const
{
    return account->getType();
}

QString Account::getId() const
{
    if(accountId.isEmpty()) {
        return account->getId();
    } else {
        return accountId;
    }
}

QString Account::getDisplayName() const
{
    if(nickname.isEmpty()) {
        return account->getDisplayName();
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

bool Account::connectToServer()
{
    connectedStatus = account->connectToServer();
    return connectedStatus;
}

void Account::disconnectFromServer()
{
    account->disconnectFromServer();
}

void Account::sendMessage(const ChatMessage *msg)
{
    account->sendMessage(msg);
}

void Account::addContact(Contact *contact)
{
    contacts.append(contact);
}

void Account::setStatus(Status *status)
{
    Person::setStatus(status);
}

void Account::setAccountObject(AccountInterface *account)
{
    this->account = account;
    account->setAccountObject(this);
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

void Account::remove()
{
    account->remove();
}

void Account::save() const
{
    account->save();
}

void Account::load()
{
    account->load();
}
