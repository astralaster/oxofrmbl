#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "common.h"
#include "Chat.h"
#include "Account.h"

class ChatMessage: public QObject
{
    Q_OBJECT

public:
    ChatMessage(Chat *chat, bool incoming, const QString &body);

    bool isIncoming() const {return incoming;}

    const Account *getLocalParticipant() const;
    const Contact *getRemoteParticipant() const;

    bool isEmpty() const;

    QString getBody() const;

private:
    Chat *chat;

    bool incoming;
    QString body;
    
};

#endif // CHATMESSAGE_H
