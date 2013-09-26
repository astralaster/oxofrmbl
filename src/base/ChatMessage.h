#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "Contact.h"
#include "Account.h"

class Contact;
class Account;

class ChatMessage: public QObject
{
    Q_OBJECT

public:
    ChatMessage(Contact *contact, const QString &body);

    const Account *getSender() const;
    Contact *getRecipient() const {return contact;}

    QString getBody() const {return body;}

private:
    Contact *contact;
    QString body;
    
};

#endif // CHATMESSAGE_H
