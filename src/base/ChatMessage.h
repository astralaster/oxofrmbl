#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QObject>

#include "common.h"

class ChatMessage: public QObject
{
    Q_OBJECT

public:
    ChatMessage(ChatSession *session, bool incoming, const QString &body);
    ~ChatMessage();

    bool isIncoming() const {return incoming;}

    const Account *getLocalParticipant() const;
    const Contact *getRemoteParticipant() const;

    bool isEmpty() const;

    QString getBody() const;

private:
    ChatSession *Session = nullptr;

    bool incoming;
    QString body;
    
};

#endif // CHATMESSAGE_H
