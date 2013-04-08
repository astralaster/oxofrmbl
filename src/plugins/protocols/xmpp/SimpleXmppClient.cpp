#include "SimpleXmppClient.h"


SimpleXmppClient::SimpleXmppClient()
{
    client = new QXmppClient();
    client->logger()->setLoggingType(QXmppLogger::StdoutLogging);

    connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));
    connect(client, SIGNAL(messageReceived(const QXmppMessage &)), this, SLOT(messageReceivedSlot(const QXmppMessage &)));
}

void SimpleXmppClient::connectToServer(const QString &address, const QString &user, const QString &password)
{
    client->connectToServer(user+"@"+address, password);
}


void SimpleXmppClient::sendMessage(const ChatMessage &msg)
{
    client->sendMessage(msg.getContact()->getId(), msg.getBody());
}

void SimpleXmppClient::connectedSlot()
{
    emit connected();
}

void SimpleXmppClient::messageReceivedSlot(const QXmppMessage &msg)
{
    emit messageReceived(msg.body());
}
