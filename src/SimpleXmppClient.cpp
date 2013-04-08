#include "SimpleXmppClient.h"


SimpleXmppClient::SimpleXmppClient()
{
    client = new QXmppClient();
    client->logger()->setLoggingType(QXmppLogger::StdoutLogging);

    connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));
    connect(client, SIGNAL(messageReceived(const QXmppMessage &)), this, SLOT(messageReceivedSlot(const QXmppMessage &)));
}

void SimpleXmppClient::connectToServer(QString jabberId, QString password)
{
    client->connectToServer(jabberId, password);
}

void SimpleXmppClient::sendMessage(QString to, QString message)
{
    client->sendMessage(to, message);
}

void SimpleXmppClient::connectedSlot()
{
    emit connected();
}

void SimpleXmppClient::messageReceivedSlot(const QXmppMessage &msg)
{
    emit messageReceived(msg.body());
}
