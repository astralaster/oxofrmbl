#include "ChatSession.h"

#include "Account.h"
#include "Contact.h"
#include "ChatMessage.h"

ChatSession::ChatSession(Contact *contact, Account *account) : QObject(account),
    m_contact(contact), m_account(account)
{
    connect(account, &Account::messageReceived, this, &ChatSession::messageReceivedSlot);
    connect(account, &Account::stateUpdateReceived, this, &ChatSession::chatStateChanged);
}

ChatSession::~ChatSession()
{
}

void ChatSession::sendMessage(const ChatMessage *msg)
{
    m_account->sendMessage(msg);
}

void ChatSession::sendStateUpdate(ChatSession::State state)
{
    m_state = state;
    m_account->sendStateUpdate(contact(), state);
}

void ChatSession::messageReceivedSlot(const ChatMessage *msg)
{
    if(msg->remoteParticipant()->id() == m_contact->id()) {
        emit messageReceived(msg);
    }
}
