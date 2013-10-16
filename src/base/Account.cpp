#include "Account.h"

#include <QRegExp>
#include <QDebug>

#include "Status.h"
#include "ChatMessage.h"
#include "Contact.h"
#include "ChatSession.h"

Account::Account(QObject *parent) : Person(parent)
{
}

Account::~Account()
{
    qDebug() << "~Account";
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

Contact *Account::contact(const QString &id)
{
    for(auto c: contacts()) {
        if(id == c->id()) {
            return c;
        }
    }
    
    return nullptr;
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

void Account::acceptContact(Contact *contact)
{
    addContact(contact);
}

void Account::refuseContact(Contact *contact)
{
    removeContact(contact);
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

void Account::addContact(Contact *c)
{
    if(contact(c->id()) == nullptr) {
        m_contacts.append(c);
        connect(c, &Contact::statusChanged, this, &Account::contactStatusChangedSlot);
        
        emit contactAdded(c);
    }
}

void Account::removeContact(Contact *c)
{
    if(contact(c->id()) != nullptr) {
        m_contacts.removeOne(c);
        emit contactRemoved(c);
        
        delete c;
    }
}

ChatSession *Account::startSession(Contact *contact)
{
    ChatSession *session;

    if(!m_chatSessions.contains(contact->id()))
    {
        session = new ChatSession(contact, this);

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
    auto contact = session->contact();

    if(contact != nullptr) {
        m_chatSessions.remove(contact->id());
        delete session;
    }
}

void Account::clearContacts()
{
    m_contacts.clear();
}
