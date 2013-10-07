#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>

#include "common.h"

#include "Account.h"
#include "Contact.h"
#include "ChatMessage.h"

class ChatMessage;

class ChatSession : public QObject
{
    Q_OBJECT
public:
    ChatSession(Contact *contact, Account *account);
    ~ChatSession();

    Contact *contact() {return m_contact;}
    Account *account() {return m_account;}

signals:
    void messageReceived(const ChatMessage *msg);

public slots:
    void sendMessage(const ChatMessage *msg);

private slots:
    void messageReceivedSlot(const ChatMessage *msg);

private:
    Contact *m_contact = nullptr;
    Account *m_account = nullptr;
};

#endif // CONVERSATION_H
