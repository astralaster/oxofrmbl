#include "XmppAccount.h"

#include <QSettings>

#include <qxmpp/QXmppRosterManager.h>

#include "base/ChatMessage.h"

#include "XmppPlugin.h"
#include "XmppContact.h"

XmppAccount::XmppAccount()
{

}

XmppAccount::~XmppAccount()
{
    delete m_client;
}

void XmppAccount::initAccount()
{
    m_client = new QXmppClient();

    m_client->logger()->setLoggingType(QXmppLogger::StdoutLogging);
    
    connect(m_client, &QXmppClient::error, this, &Account::error);

    connect(&m_client->rosterManager(), &QXmppRosterManager::rosterReceived, this, &XmppAccount::retrieveContacts);
    connect(m_client, &QXmppClient::messageReceived, this, &XmppAccount::messageReceivedSlot);
    
    connect(m_client, &QXmppClient::presenceReceived, this, &XmppAccount::presenceReceivedSlot);
    
    connect(m_client, &QXmppClient::disconnected, this, &XmppAccount::disconnected);
    connect(this, &XmppAccount::disconnected, this, &XmppAccount::clearContacts);
}

void XmppAccount::retrieveContacts()
{
    for(auto contact_jid: m_client->rosterManager().getRosterBareJids()) {
        auto resources = m_client->rosterManager().getResources(contact_jid);
        Account::addContact(new XmppContact(this, contact_jid, resources));
    }

    emit connected();
}

void XmppAccount::remove()
{
    m_client->disconnectFromServer();
    QSettings().remove(QString("accounts/xmpp/%1/").arg(id()));
}

void XmppAccount::save() const
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(id()));

    settings.setValue("server", m_server);
    settings.setValue("user", m_user);
    settings.setValue("password", m_password);

    settings.endGroup();
    
    emit accountSaved();
}

void XmppAccount::load()
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(id()));

    m_server = settings.value("server", m_server).toString();
    m_user = settings.value("user", m_user).toString();
    m_password = settings.value("password", m_password).toString();

    settings.endGroup();
}

QString XmppAccount::server() const
{
    return m_server;
}

QString XmppAccount::user() const
{
    return m_user;
}

QString XmppAccount::password() const
{
    return m_password;
}

QString XmppAccount::resource() const
{
    return m_resource;
}

QString XmppAccount::type() const
{
    return "xmpp";
}

QString XmppAccount::id() const
{
    if(m_id.isEmpty()) {
        return m_user+"@"+m_server;
    } else {
        return m_id;
    }
}

QString XmppAccount::displayName() const
{
    return id();
}

bool XmppAccount::connectToServer()
{
    m_client->connectToServer(m_user+"@"+m_server, m_password);
    return true;
}

void XmppAccount::disconnectFromServer()
{
    m_client->disconnectFromServer();
    emit disconnected();
}

void XmppAccount::sendMessage(const ChatMessage *msg)
{
    m_client->sendMessage(msg->remoteParticipant()->id(), msg->body());
}

void XmppAccount::setState(const QString &server, const QString &user, const QString &password, const QString &resource)
{
    setServer(server);
    setUser(user);
    setPassword(password);
    setResource(resource);
}

void XmppAccount::setServer(const QString &server)
{
    m_server = server;
}

void XmppAccount::setUser(const QString &user)
{
    m_user = user;
}

void XmppAccount::setPassword(const QString &password)
{
    m_password = password;
}

void XmppAccount::setResource(const QString &resource)
{
    m_resource = resource;
}

void XmppAccount::setStatus(Status *status)
{
    QXmppPresence presence;

    presence << *status;

    m_client->setClientPresence(presence);

    if(presence.type() == QXmppPresence::Unavailable) {
        disconnectFromServer();
    }
    
    Account::setStatus(status);
}

Contact *XmppAccount::createContact(const QString &contactId)
{
    return new XmppContact(this, contactId);
}

void XmppAccount::addContact(Contact *contact)
{
    QString jid = contact->id();
    
    if(m_client->rosterManager().addItem(jid)) {
        //QXmppPresence presence = m_client->rosterManager().getPresence(jid, "desktop");
        //*contact->status() << presence;
        Account::addContact(contact);
    }
}

void XmppAccount::removeContact(Contact *contact)
{
    if(m_client->rosterManager().removeItem(contact->id())) {
        Account::removeContact(contact);
    }
}

void XmppAccount::clearContacts()
{
    m_contacts.clear();
}

void XmppAccount::messageReceivedSlot(const QXmppMessage &msg)
{
    if(msg.type() != QXmppMessage::Chat) {
        return;
    }

    auto from = XmppContact::parseJabberId(msg.from());
    auto _session = session(from[0]+"@"+from[1]);

    if((msg.state() == QXmppMessage::Active || !msg.state()) && !msg.body().isEmpty()) {
        if(_session == nullptr) {
            auto contact = new XmppContact(this, msg.from());

            _session = startSession(contact);
        }

        auto message = new ChatMessage(_session, true, msg.body(), msg.stamp());
        emit messageReceived(message);
    }
}


void XmppAccount::presenceReceivedSlot(const QXmppPresence &presence)
{
    auto from = XmppContact::parseJabberId(presence.from());
    auto jid = from[0]+"@"+from[1];
    
    if(jid == id()) {
        return;
    }
    
    Contact *contact = nullptr;
    
    for(Contact *c: m_contacts) {
        if(c->id() == jid) {
            contact = c;
            break;
        }
    }
    
    if(contact != nullptr) {
        contact->setStatus(&(*contact->status() << presence));
    }
}
