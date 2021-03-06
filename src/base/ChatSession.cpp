#include "ChatSession.h"

#include "Account.h"
#include "Contact.h"
#include "ChatMessage.h"
#include "FileTransfer.h"

ChatSession::ChatSession(Contact *contact, Account *account) : QObject(account),
    m_contact(contact), m_account(account)
{
    connect(account, &Account::messageReceived, this, &ChatSession::messageReceivedSlot);
    connect(account, &Account::fileReceived, this, &ChatSession::fileReceivedSlot);
    connect(account, &Account::stateUpdateReceived, this, &ChatSession::chatStateChangedSlot);
}

ChatSession::~ChatSession()
{
    qDebug() << "~ChatSession";
}

void ChatSession::sendMessage(ChatMessage *msg)
{
    m_account->sendMessage(msg);
}

void ChatSession::sendStateUpdate(ChatSession::State state)
{
    m_state = state;
    m_account->sendStateUpdate(contact(), state);
}

void ChatSession::chatStateChangedSlot(Contact *contact, ChatSession::State state)
{
    if(contact->id() == m_contact->id()) {
        emit chatStateChanged(state);
    }
}

void ChatSession::messageReceivedSlot(ChatMessage *msg)
{
    if(msg->contact()->id() == m_contact->id()) {
        emit messageReceived(msg);
    }
}

void ChatSession::fileReceivedSlot(FileTransfer *transfer)
{
    if(transfer->contact()->id() == m_contact->id()) {
        emit fileReceived(transfer);
    }
}
