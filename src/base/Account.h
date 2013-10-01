#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>

#include "common.h"
#include "ChatMessage.h"
#include "Contact.h"

class Account : public Person
{
    Q_OBJECT
public:
    explicit Account(QObject *parent = 0);
    ~Account();

    ChatSession *getSession(const QString &contactId);

    QMap<QString, ChatSession*> getSessions();
    QList<Contact*> getContacts();

    bool isActive() const;

signals:
    void sessionStarted(ChatSession *session);
    void sessionActivated(ChatSession *session);
    void messageReceived(const ChatMessage *msg);
    void connected();
    void disconnected();

public slots:
    virtual bool connectToServer() = 0;
    virtual void disconnectFromServer() = 0;
    virtual void sendMessage(const ChatMessage *msg) = 0;

    virtual void addContact(Contact *contact);

    virtual ChatSession *startSession(Contact *contact);
    virtual void endSession(ChatSession *session);

    virtual void save() const = 0;
    virtual void load() = 0;

protected:
    bool active = true;

    QList<Contact*> contacts;
    QMap<QString, ChatSession*> chatSessions;
};

#endif // ACCOUNT_H
