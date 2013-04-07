#include "SimpleXmppClient.h"

SimpleXmppClient::SimpleXmppClient()
{
    client = new QXmppClient();
    client->logger()->setLoggingType(QXmppLogger::StdoutLogging);
}

void SimpleXmppClient::connectToServer(QString jabberId, QString password)
{
    connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));

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
