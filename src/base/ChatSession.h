#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>

#include "common.h"

class ChatSession : public QObject
{
    Q_OBJECT
public:
    ChatSession(Contact *contact, Account *account);
    ~ChatSession();

    Contact *getContact() {return contact;}
    Account *getAccount() {return account;}

signals:
    void messageReceived(const ChatMessage *msg);

public slots:
    void sendMessage(const ChatMessage *msg);

private slots:
    void messageReceivedSlot(const ChatMessage *msg);

private:
    Contact *contact = nullptr;
    Account *account = nullptr;
};

#endif // CONVERSATION_H
