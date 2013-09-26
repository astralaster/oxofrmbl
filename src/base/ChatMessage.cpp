#include "ChatMessage.h"


ChatMessage::ChatMessage(Contact *contact, const QString &body) :
    contact(contact), body(body)
{
}

const Account *ChatMessage::getSender() const
{
    return contact->getAccount();
}
