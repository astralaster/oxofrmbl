#include "Conversation.h"

#include <QDebug>

Conversation::Conversation(Contact *contact, Account *account) :
    contact(contact), account(account)
{
    connect(account, &Account::messageReceived, this, &Conversation::messageReceivedSlot);
}

void Conversation::sendMessage(const ChatMessage *msg)
{
    account->sendMessage(msg);
}

void Conversation::messageReceivedSlot(const ChatMessage *msg)
{
    qDebug() << msg->getRemoteParticipant()->getId() << contact->getId();

    if(msg->getRemoteParticipant()->getId() == contact->getId()) {
        emit messageReceived(msg);
    }
}
