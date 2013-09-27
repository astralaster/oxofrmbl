#include "Account.h"

#include <QDebug>

Account::Account()
{

}

Chat *Account::startChat(Contact *contact)
{
    Chat *chat;

    if(!chats.contains(contact->getId())) {
        chat = new Chat(contact, this);

        chats[contact->getId()] = chat;

        emit chatStarted(chat);
    } else {
        chat = chats[contact->getId()];
        emit chatActivated(chat);
    }

    return chat;
}

Chat *Account::getChat(const QString &contactId)
{
    return chats.contains(contactId) ? chats[contactId] : nullptr;
}

QMap<QString, Chat*> Account::getChats()
{
    return chats;
}

void Account::endChat(Chat *chat)
{
    chats.remove(chat->getContact()->getId());
    delete chat;
}