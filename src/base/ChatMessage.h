#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "ChatContact.h"

class ChatMessage
{

public:
    ChatMessage(ChatContact *contact, const QString &body);
    ChatContact *getContact() const {return contact;}
    QString getBody() const {return body;}

private:
    ChatContact *contact;
    QString body;
    
};

#endif // CHATMESSAGE_H
