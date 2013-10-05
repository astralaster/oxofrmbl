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
    delete client;
}

void XmppAccount::initAccount()
{
    client = new QXmppClient();

    client->logger()->setLoggingType(QXmppLogger::StdoutLogging);

    connect(&client->rosterManager(), &QXmppRosterManager::rosterReceived, this, &XmppAccount::retrieveContacts);
    connect(client, &QXmppClient::messageReceived, this, &XmppAccount::messageReceivedSlot);
    
    connect(client, &QXmppClient::presenceReceived, this, &XmppAccount::presenceReceivedSlot);
    
    connect(client, &QXmppClient::disconnected, this, &XmppAccount::disconnected);
    connect(this, &XmppAccount::disconnected, this, &XmppAccount::clearContacts);
}

void XmppAccount::retrieveContacts()
{
    for(auto contact_jid: client->rosterManager().getRosterBareJids()) {
        addContact(new XmppContact(this, contact_jid));
    }

    emit connected();
}

void XmppAccount::remove()
{
    client->disconnectFromServer();
    QSettings().remove(QString("accounts/xmpp/%1/").arg(getId()));
}

void XmppAccount::save() const
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(getId()));

    settings.setValue("server", server);
    settings.setValue("user", user);
    settings.setValue("password", password);

    settings.endGroup();
    
    emit accountSaved();
}

void XmppAccount::load()
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(getId()));

    server = settings.value("server", server).toString();
    user = settings.value("user", user).toString();
    password = settings.value("password", password).toString();

    settings.endGroup();
}

QString XmppAccount::getServer() const
{
    return server;
}

QString XmppAccount::getUser() const
{
    return user;
}

QString XmppAccount::getPassword() const
{
    return password;
}

QString XmppAccount::getResource() const
{
    return resource;
}

QString XmppAccount::getType() const
{
    return "xmpp";
}

QString XmppAccount::getId() const
{
    if(accountId.isEmpty()) {
        return user+"@"+server;
    } else {
        return accountId;
    }
}

QString XmppAccount::getDisplayName() const
{
    return getId();
}

bool XmppAccount::connectToServer()
{
    client->connectToServer(user+"@"+server, password);
    return true;
}

void XmppAccount::disconnectFromServer()
{
    client->disconnectFromServer();
    emit disconnected();
}

void XmppAccount::sendMessage(const ChatMessage *msg)
{
    client->sendMessage(msg->getRemoteParticipant()->getId(), msg->getBody());
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
    this->server = server;
}

void XmppAccount::setUser(const QString &user)
{
    this->user = user;
}

void XmppAccount::setPassword(const QString &password)
{
    this->password = password;
}

void XmppAccount::setResource(const QString &resource)
{
    this->resource = resource;
}

void XmppAccount::setStatus(Status *status)
{
    QXmppPresence presence;

    presence << *status;

    client->setClientPresence(presence);

    if(presence.type() == QXmppPresence::Unavailable) {
        disconnectFromServer();
    }
    
    Account::setStatus(status);
}

void XmppAccount::clearContacts()
{
    contacts.clear();
}

void XmppAccount::messageReceivedSlot(const QXmppMessage &msg)
{
    if(msg.type() != QXmppMessage::Chat) {
        return;
    }

    auto from = XmppContact::parseJabberId(msg.from());
    auto session = getSession(from[0]+"@"+from[1]);

    if((msg.state() == QXmppMessage::Active || !msg.state()) && !msg.body().isEmpty()) {
        if(session == nullptr) {
            auto contact = new XmppContact(this, msg.from());

            session = startSession(contact);
        }

        auto message = new ChatMessage(session, true, msg.body());
        emit messageReceived(message);
    }
}


void XmppAccount::presenceReceivedSlot(const QXmppPresence &presence)
{
    auto from = XmppContact::parseJabberId(presence.from());
    auto id = from[0]+"@"+from[1];
    
    if(id == getId()) {
        return;
    }
    
    Contact *contact = nullptr;
    
    for(Contact *c: contacts) {
        if(c->getId() == id) {
            contact = c;
            break;
        }
    }
    
    if(contact != nullptr) {
        contact->setStatus(&(*contact->getStatus() << presence));
    }
}
