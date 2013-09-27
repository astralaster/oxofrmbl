#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "common.h"
#include "Conversation.h"
#include "Account.h"

class ChatMessage: public QObject
{
    Q_OBJECT

public:
    ChatMessage(Contact *remoteParticipant, bool incoming, const QString &body);

    bool isIncoming() const {return incoming;}

    const Account *getLocalParticipant() const;
    const Contact *getRemoteParticipant() const;

    QString getBody() const;

private:
    Contact *remoteParticipant;

    bool incoming;
    QString body;
    
};

#endif // CHATMESSAGE_H
