#include "XmppAccount.h"
#include "XmppContact.h"

#include <QSettings>

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

    connect(this, &XmppAccount::connected, account, &Account::connected);
    connect(&client->rosterManager(), &QXmppRosterManager::rosterReceived, this, &XmppAccount::retrieveContacts);

    connect(client, &QXmppClient::messageReceived, this, &XmppAccount::messageReceivedSlot);
    connect(this, &XmppAccount::messageReceived, account, &Account::messageReceived);

    //connect(this, &XmppAccount::disconnected, this, &XmppAccount::clearContacts);
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

void XmppAccount::retrieveContacts()
{
    for(auto contact_jid: client->rosterManager().getRosterBareJids()) {
        account->addContact(new Contact(new XmppContact(contact_jid), account));
    }

    emit connected();
}

void XmppAccount::save() const
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(account->getId()));

    settings.setValue("server", server);
    settings.setValue("user", user);
    settings.setValue("password", password);

    settings.endGroup();
    
    emit account->accountSaved();
}

void XmppAccount::load()
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(account->getId()));

    server = settings.value("server", server).toString();
    user = settings.value("user", user).toString();
    password = settings.value("password", password).toString();

    settings.endGroup();
}

QString XmppAccount::getId() const
{
    return user+"@"+server;
}

QString XmppAccount::getDisplayName() const
{
    return getId();
}

Account *XmppAccount::getAccountObject()
{
    return account;
}

void XmppAccount::setAccountObject(Account *account)
{
    this->account = account;
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

void XmppAccount::setStatus(Status status)
{
    //Person::setStatus(status);

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
    auto session = account->getSession(from[0]+"@"+from[1]);

    if((msg.state() == QXmppMessage::Active || !msg.state()) && !msg.body().isEmpty()) {
        if(session == nullptr) {
            auto contact = new Contact(new XmppContact(msg.from()), account);

            session = account->startSession(contact);
        }

        auto message = new ChatMessage(session, true, msg.body());
        emit messageReceived(message);
    }
}
