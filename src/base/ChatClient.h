#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>

#include "ChatMessage.h"

class ChatClient : public QObject
{
    Q_OBJECT
public:
    ChatClient();
    
signals:
    void messageReceived();
    void connected();
    
public slots:
    virtual void connectToServer(const QString &address, const QString &user, const QString &password) = 0;
    virtual void sendMessage(const ChatMessage &msg) = 0;
    
};

#endif // CHATCLIENT_H
