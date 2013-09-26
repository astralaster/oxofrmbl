#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>

#include "ChatMessage.h"
#include "Contact.h"

class Contact;
class ChatMessage;

class Account : public QObject
{
    Q_OBJECT
public:
    Account();

    virtual QList<Contact*> getContacts() const = 0;

signals:
    void messageReceived(const QString &msg);
    void connected();

public slots:
    virtual bool connectToServer() = 0;
    virtual void disconnectFromServer() = 0;
    virtual void sendMessage(const ChatMessage *msg) = 0;
};

#endif // ACCOUNT_H
