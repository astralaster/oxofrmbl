#include "ChatMessage.h"


ChatMessage::ChatMessage(Contact *remoteParticipant, bool incoming, const QString &body) :
    remoteParticipant(remoteParticipant), incoming(incoming), body(body)
{
}

const Account *ChatMessage::getLocalParticipant() const
{
    return remoteParticipant->getAccount();
}

const Contact *ChatMessage::getRemoteParticipant() const
{
    return remoteParticipant;
}

QString ChatMessage::getBody() const
{
    return body;
}
