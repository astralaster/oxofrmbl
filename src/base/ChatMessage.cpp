#include "ChatMessage.h"


ChatMessage::ChatMessage(Chat *chat, bool incoming, const QString &body) : QObject(chat),
    chat(chat), incoming(incoming), body(body)
{
}

const Account *ChatMessage::getLocalParticipant() const
{
    return chat->getAccount();
}

const Contact *ChatMessage::getRemoteParticipant() const
{
    return chat->getContact();
}

bool ChatMessage::isEmpty() const
{
    return body.isEmpty();
}

QString ChatMessage::getBody() const
{
    return body;
}
