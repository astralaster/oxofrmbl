#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QDateTime>
#include <QObject>

#include "common.h"

class Account;
class Contact;
class ChatSession;

class ChatMessage: public QObject
{
    Q_OBJECT

public:
    ChatMessage(ChatSession *session, bool incoming, const QString &body);
    ChatMessage(ChatSession *session, bool incoming, const QString &body, const QDateTime &time);
    ~ChatMessage();
    
    QString body() const;
    QDateTime time() const;

    const Account *account() const;
    const Contact *contact() const;

    bool isIncoming() const;
    bool isEmpty() const;

private:
    ChatSession *m_session = nullptr;
    
    QDateTime m_time;
    bool m_incoming;
    QString m_body;
    
};

#endif // CHATMESSAGE_H
