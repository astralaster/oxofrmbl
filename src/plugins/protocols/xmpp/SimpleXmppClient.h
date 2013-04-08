#ifndef SIMPLEXMPPCLIENT_H
#define SIMPLEXMPPCLIENT_H

#include "QXmppClient.h"
#include "QXmppMessage.h"

#include "ChatMessage.h"
#include "ChatClient.h"

#include "XmppContact.h"

class SimpleXmppClient : public ChatClient
{
    Q_OBJECT

public:
    SimpleXmppClient();

public slots:
    virtual void connectToServer(const QString &address, const QString &user, const QString &password);
    virtual void sendMessage(const ChatMessage &msg);

private slots:
    void connectedSlot();
    void messageReceivedSlot(const QXmppMessage &message);

signals:
    void connected();
    void messageReceived(QString msg);

private:
    QXmppClient *client;
};

#endif // SIMPLEXMPPCLIENT_H
