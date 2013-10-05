#include "ChatSession.h"

#include "Account.h"
#include "Contact.h"
#include "ChatMessage.h"

ChatSession::ChatSession(Contact *contact, Account *account) : QObject(account),
    contact(contact), account(account)
{
    connect(account, &Account::messageReceived, this, &ChatSession::messageReceivedSlot);
}

ChatSession::~ChatSession()
{
}

void ChatSession::sendMessage(const ChatMessage *msg)
{
    account->sendMessage(msg);
}

void ChatSession::messageReceivedSlot(const ChatMessage *msg)
{
    if(msg->getRemoteParticipant()->getId() == contact->getId()) {
        emit messageReceived(msg);
    }
}
