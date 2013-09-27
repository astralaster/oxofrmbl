#include "XmppAccount.h"
#include "XmppContact.h"

XmppAccount::XmppAccount(const QString &server, const QString &user, const QString &password) : Account(),
    client(new QXmppClient()), server(server), user(user), password(password)

{
    client->logger()->setLoggingType(QXmppLogger::StdoutLogging);

    connect(&client->rosterManager(), &QXmppRosterManager::rosterReceived, this, &XmppAccount::connectedSlot);

    connect(client, &QXmppClient::connected, this, &XmppAccount::connectedSlot);
    connect(client, &QXmppClient::messageReceived, this, &XmppAccount::messageReceivedSlot);
}

XmppAccount::~XmppAccount()
{
    delete client;
}

QList<Contact*> XmppAccount::getContacts()
{
    QList<Contact*> contacts;

    for(auto contact_jid: client->rosterManager().getRosterBareJids()) {
        contacts.append(new XmppContact(this, contact_jid));
    }

    return contacts;
}

QString XmppAccount::getDisplayName() const
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
}

void XmppAccount::sendMessage(const ChatMessage *msg)
{
    client->sendMessage(msg->getRemoteParticipant()->getId(), msg->getBody());
}

void XmppAccount::connectedSlot()
{
    emit connected();
}

void XmppAccount::messageReceivedSlot(const QXmppMessage &msg)
{
    if(msg.type() != QXmppMessage::Chat) {
        return;
    }

    auto from = XmppContact::parseJabberId(msg.from());
    auto chat = getChat(from[0]+"@"+from[1]);

    if(chat == nullptr) {
        chat = startChat(new XmppContact(this, msg.from()));
    }

    auto message = new ChatMessage(chat, true, msg.body());
    emit messageReceived(message);
}