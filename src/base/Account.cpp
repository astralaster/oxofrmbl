#include "Account.h"

#include <QDebug>

Account::Account(AccountInterface *account, QObject *parent) : Person(parent), account(account)
{
}

Account::~Account()
{
}

void Account::initAccount()
{
    account->initAccount();
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

PersonInterface::Status Account::getStatus() const
{
    return status;
}

void Account::setId(const QString &id)
{
    accountId = id;
}

bool Account::isActive() const
{
    return active;
}

bool Account::connectToServer()
{
    return account->connectToServer();
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

void Account::setStatus(Status status)
{
    this->status = status;
    account->setStatus(status);
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

void Account::save() const
{
    account->save();
}

void Account::load()
{
    account->load();
}