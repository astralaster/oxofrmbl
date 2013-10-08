#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>

#include "common.h"
#include "Person.h"

#include "ChatSession.h"
#include "ChatMessage.h"
#include "MessageHandler.h"

class MessageHandler;

class Account : public Person
{
    Q_OBJECT
public:
    explicit Account(QObject *parent = nullptr);
    ~Account();
    
    virtual QString type() const = 0;
    virtual QString id() const = 0;
    virtual QString displayName() const = 0;
    
    ChatSession *session(const QString &contactId);
    //ChatSession *session(const QRegExp &contatcIdPattern);
    QMap<QString, ChatSession*> sessions();
    QList<Contact*> contacts();

    Status *status();

    bool isConnected() const;
    bool isActive() const;

signals:
    void sessionStarted(ChatSession *session);
    void sessionActivated(ChatSession *session);
    
    void messageReceived(const ChatMessage *msg);
    void contactStatusChanged(Contact *contact, Status *status);
    
    void contactAdded(Contact *contact);
    void contactRemoved(Contact *contact);
    
    void error();
   
    void connected();
    void disconnected();
    void accountSaved() const;

public slots:
    void contactStatusChangedSlot(Status *status);
    
    virtual bool connectToServer() = 0;
    virtual void disconnectFromServer() = 0;
    virtual void sendMessage(const ChatMessage *msg) = 0;

    virtual void remove() = 0;
    virtual void save() const = 0;
    virtual void load() = 0;
    
    virtual void initAccount() = 0;
    
    virtual Contact *createContact(const QString &contactId) = 0;
    virtual void addContact(Contact *contact);
    virtual void removeContact(Contact *contact);

    virtual ChatSession *startSession(Contact *contact);
    virtual void endSession(ChatSession *session);
    
    virtual void installMessageHandler(MessageHandler *handler);
    virtual void removeMessageHandler(MessageHandler *handler);

protected:
    bool connectedStatus = false;
    bool active = true;

    QList<Contact*> m_contacts;
    QList<MessageHandler*> m_messageHandlers;
    QMap<QString, ChatSession*> m_chatSessions;
};

#endif // ACCOUNT_H
