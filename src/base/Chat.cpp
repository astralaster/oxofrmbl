#include "Chat.h"

#include <QDebug>

Chat::Chat(Contact *contact, Account *account) : QObject(account),
    contact(contact), account(account)
{
    connect(account, &Account::messageReceived, this, &Chat::messageReceivedSlot);
}

void Chat::sendMessage(const ChatMessage *msg)
{
    account->sendMessage(msg);
}

void Chat::messageReceivedSlot(const ChatMessage *msg)
{
    if(msg->getRemoteParticipant()->getId() == contact->getId()) {
        emit messageReceived(msg);
    }
}
