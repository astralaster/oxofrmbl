#include "XmppAccount.h"
#include "XmppContact.h"

#include <QSettings>

XmppAccount::XmppAccount(const QString &server, const QString &user, const QString &password) :
    Account(), client(new QXmppClient()), server(server), user(user), password(password)
{
    client->logger()->setLoggingType(QXmppLogger::StdoutLogging);

    connect(&client->rosterManager(), &QXmppRosterManager::rosterReceived, this, &XmppAccount::retrieveContacts);

    connect(client, &QXmppClient::connected, this, &XmppAccount::connected);
    connect(client, &QXmppClient::messageReceived, this, &XmppAccount::messageReceivedSlot);

    connect(this, &XmppAccount::disconnected, this, &XmppAccount::clearContacts);
}

XmppAccount::~XmppAccount()
{
    delete client;
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

void XmppAccount::retrieveContacts()
{
    for(auto contact_jid: client->rosterManager().getRosterBareJids()) {
        contacts.append(new XmppContact(this, contact_jid));
    }

    emit connected();
}

void XmppAccount::clearContacts()
{
    contacts.clear();
}

void XmppAccount::save() const
{
    QString key = QString("accounts/xmpp/%1/%2").arg(getId()).arg("%1");

    QSettings().setValue(key.arg("server"), server);
    QSettings().setValue(key.arg("user"), user);
    QSettings().setValue(key.arg("password"), password);
}

void XmppAccount::load()
{
    QString key = QString("accounts/xmpp/%1/%2").arg(getId()).arg("%1");

    server = QSettings().value(key.arg("server")).toString();
    user = QSettings().value(key.arg("user")).toString();
    password = QSettings().value(key.arg("password")).toString();
}

QString XmppAccount::getId() const
{
    return user+"@"+server;
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

void XmppAccount::setStatus(Person::Status status)
{
    Person::setStatus(status);

    QXmppPresence presence;

    switch (status) {
    case Status::Away:
        presence.setType(QXmppPresence::Available);
        presence.setAvailableStatusType(QXmppPresence::Away);
        break;

    case Status::Offline:
        presence = QXmppPresence::Unavailable;
        presence.setType(QXmppPresence::Unavailable);
        presence.setAvailableStatusType(QXmppPresence::Away);
        break;

    case Status::Online:
    default:
        presence.setType(QXmppPresence::Available);
        presence.setAvailableStatusType(QXmppPresence::Online);
        break;
    }

    client->setClientPresence(presence);

    if(presence.type() == QXmppPresence::Unavailable) {
        disconnectFromServer();
    }
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
            session = startSession(new XmppContact(this, msg.from()));
        }

        auto message = new ChatMessage(session, true, msg.body());
        emit messageReceived(message);
    }
}