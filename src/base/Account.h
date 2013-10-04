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
    
    virtual QString getType() const = 0;
    virtual QString getId() const = 0;
    virtual QString getDisplayName() const = 0;
    
    ChatSession *getSession(const QString &contactId);
    QMap<QString, ChatSession*> getSessions();
    QList<Contact*> getContacts();

    Status *getStatus();

    bool isConnected() const;
    bool isActive() const;

signals:
    void sessionStarted(ChatSession *session);
    void sessionActivated(ChatSession *session);
    void messageReceived(const ChatMessage *msg);
    void connected();
    void disconnected();
    void accountSaved() const;

public slots:
    virtual bool connectToServer() = 0;
    virtual void disconnectFromServer() = 0;
    virtual void sendMessage(const ChatMessage *msg) = 0;

    virtual void remove() = 0;
    virtual void save() const = 0;
    virtual void load() = 0;
    
    virtual void initAccount() = 0;
    
    void setId(const QString &id);
    void setStatus(Status *status);
    
    void addContact(Contact *contact);

    ChatSession *startSession(Contact *contact);
    void endSession(ChatSession *session);

protected:
    QString accountId;

    bool connectedStatus = false;
    bool active = true;

    QList<Contact*> contacts;
    QMap<QString, ChatSession*> chatSessions;
};

#endif // ACCOUNT_H
