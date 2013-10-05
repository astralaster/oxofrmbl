#include "ChatMessage.h"

#include <QDebug>

#include "Account.h"
#include "ChatSession.h"

ChatMessage::ChatMessage(ChatSession *session, bool incoming, const QString &body) : QObject(session),
    Session(session), incoming(incoming), body(body)
{
}

ChatMessage::~ChatMessage()
{
}

const Account *ChatMessage::getLocalParticipant() const
{
    return Session->getAccount();
}

const Contact *ChatMessage::getRemoteParticipant() const
{
    return Session->getContact();
}

bool ChatMessage::isEmpty() const
{
    return body.isEmpty();
}

QString ChatMessage::getBody() const
{
    return body;
}
