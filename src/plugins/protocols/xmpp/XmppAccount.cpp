#include "XmppAccount.h"
#include "XmppContact.h"

XmppAccount::XmppAccount(const QString &server, const QString &user, const QString &password) :
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

QList<Contact*> XmppAccount::getContacts() const
{
    QList<Contact*> contacts;

    for(auto contact_jid: client->rosterManager().getRosterBareJids()) {
        contacts.append(new XmppContact(this, contact_jid));
    }

    return contacts;
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
    client->sendMessage(msg->getRecipient()->getId(), msg->getBody());
}

void XmppAccount::connectedSlot()
{
    emit connected();
}

void XmppAccount::messageReceivedSlot(const QXmppMessage &msg)
{
    emit messageReceived(msg.body());
}