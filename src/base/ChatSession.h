#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>

#include "common.h"

class Account;
class Contact;
class ChatMessage;

class ChatSession : public QObject
{
    Q_OBJECT
public:
    enum class State {
        Unknown = 0,
        Composing,
        Paused,
        Gone
    };

    ChatSession(Contact *contact, Account *account);
    ~ChatSession();

    Contact *contact() {return m_contact;}
    Account *account() {return m_account;}

signals:
    void messageReceived(const ChatMessage *msg);
    void chatStateChanged(State state);

public slots:
    void sendMessage(const ChatMessage *msg);
    void sendStateUpdate(State state);

private slots:
    void messageReceivedSlot(const ChatMessage *msg);

private:
    State m_state;
    Contact *m_contact = nullptr;
    Account *m_account = nullptr;
};

#endif // CONVERSATION_H
