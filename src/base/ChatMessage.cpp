#include "ChatMessage.h"


ChatMessage::ChatMessage(ChatContact *contact, const QString &body) :
    contact(contact), body(body)
{
}
