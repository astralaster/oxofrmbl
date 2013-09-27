#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>

#include "common.h"
#include "Contact.h"
#include "Account.h"

class Chat : public QObject
{
    Q_OBJECT
public:
    Chat(Contact *contact, Account *account);
    Contact *getContact() {return contact;}
    Account *getAccount() {return account;}

signals:
    void messageReceived(const ChatMessage *msg);

public slots:
    void sendMessage(const ChatMessage *msg);

private slots:
    void messageReceivedSlot(const ChatMessage *msg);

private:
    Contact *contact;
    Account *account;
};

#endif // CONVERSATION_H
