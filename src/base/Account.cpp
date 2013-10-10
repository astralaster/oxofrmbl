#include "Account.h"

#include <QRegExp>
#include <QDebug>

#include "Status.h"
#include "ChatMessage.h"
#include "Contact.h"
#include "ChatSession.h"
#include "MessageHandler.h"

Account::Account(QObject *parent) : Person(parent)
{
}

Account::~Account()
{
}

ChatSession *Account::session(const QString &contactId)
{
    return m_chatSessions.contains(contactId) ? m_chatSessions[contactId] : nullptr;
}

QList<ChatSession*> Account::sessions(const QRegExp &contatcIdPattern)
{
    QList<ChatSession*> result;
    
    for(ChatSession *session: sessions())
    {
        if(contatcIdPattern.exactMatch(session->contact()->id()))
        {
            result << session;
        }
    }
    
    return result;
}

QMap<QString, ChatSession*> Account::sessions()
{
    return m_chatSessions;
}

QList<Contact*> Account::contacts()
{
    return m_contacts;
}

/*QString Account::getId() const
{
    if(accountId.isEmpty()) {
        return account->getId();
    } else {
        return accountId;
    }
}*/

QString Account::displayName() const
{
    if(m_nickname.isEmpty()) {
        return displayName();
    } else {
        return m_nickname;
    }
}

Status *Account::status()
{
    return m_status;
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
    auto sender = qobject_cast<Contact*>(QObject::sender());

    if(sender != nullptr) {
        emit contactStatusChanged(sender, status);
    } else {
        qDebug() << "sender is null";
    }
}

void Account::addContact(Contact *contact)
{
    m_contacts.append(contact);
    connect(contact, &Contact::statusChanged, this, &Account::contactStatusChangedSlot);
    
    emit contactAdded(contact);
}

void Account::removeContact(Contact *contact)
{
    m_contacts.removeOne(contact);
    emit contactRemoved(contact);
    
    delete contact;
}

ChatSession *Account::startSession(Contact *contact)
{
    ChatSession *session;

    if(!m_chatSessions.contains(contact->id()))
    {
        session = new ChatSession(contact, this);
        qDebug() << contact;

        m_chatSessions[contact->id()] = session;

        emit sessionStarted(session);
    } else {
        session = m_chatSessions[contact->id()];
        emit sessionActivated(session);
    }

    return session;
}

void Account::endSession(ChatSession *session)
{
    m_chatSessions.remove(session->contact()->id());
    delete session;
}

void Account::installMessageHandler(MessageHandler *handler)
{
    m_messageHandlers.append(handler);
}

void Account::removeMessageHandler(MessageHandler *handler)
{
    m_messageHandlers.removeOne(handler);
}
