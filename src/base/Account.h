#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>

#include "common.h"
#include "ChatMessage.h"
#include "Contact.h"

class Account : public QObject
{
    Q_OBJECT
public:
    Account();

    Chat *startChat(Contact *contact);
    virtual Chat *getChat(const QString &contactId);

    virtual QString getDisplayName() const = 0;
    virtual QMap<QString, Chat*> getChats();
    virtual QList<Contact*> getContacts() = 0;

signals:
    void chatStarted(Chat *chat);
    void chatActivated(Chat *chat);
    void messageReceived(const ChatMessage *msg);
    void connected();

public slots:
    virtual bool connectToServer() = 0;
    virtual void disconnectFromServer() = 0;
    virtual void sendMessage(const ChatMessage *msg) = 0;

    virtual void endChat(Chat *chat);

protected:
    QMap<QString, Chat*> chats;
};

#endif // ACCOUNT_H
