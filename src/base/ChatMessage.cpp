#include "ChatMessage.h"

#include "Account.h"
#include "ChatSession.h"

ChatMessage::ChatMessage(ChatSession *session, bool incoming, const QString &body) :
    ChatMessage(session, incoming, body, QDateTime())
{
}

ChatMessage::ChatMessage(ChatSession *session, bool incoming, const QString &body, const QDateTime &time) : QObject(session),
    m_session(session), m_incoming(incoming), m_body(body)
{
    if(time.isNull()) {
        m_time.setDate(QDate::currentDate());
        m_time.setTime(QTime::currentTime());
    }
}

ChatMessage::~ChatMessage()
{
}

bool ChatMessage::isIncoming() const
{
    return m_incoming;
}

const Account *ChatMessage::localParticipant() const
{
    return m_session->account();
}

const Contact *ChatMessage::remoteParticipant() const
{
    return m_session->contact();
}

bool ChatMessage::isEmpty() const
{
    return m_body.isEmpty();
}

QString ChatMessage::body() const
{
    return m_body;
}

QDateTime ChatMessage::time() const
{
    return m_time;
}
