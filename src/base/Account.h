#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QFile>

#include "common.h"
#include "Person.h"

#include "ChatSession.h"
#include "ChatMessage.h"
#include "MessageHandler.h"
#include "FileTransfer.h"

class ChatSession;
class ChatMessage;
class FileTransfer;

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
    QList<ChatSession*> sessions(const QRegExp &contatcIdPattern);
    QMap<QString, ChatSession*> sessions();
    Contact *contact(const QString &id);
    QList<Contact*> contacts();

    Status *status();

    bool isConnected() const;
    bool isActive() const;

signals:
    void sessionStarted(ChatSession *session);
    void sessionActivated(ChatSession *session);
    
    void contactAdded(Contact *contact);
    void contactRemoved(Contact *contact);
    
signals:
    void contactRequestReceived(Contact *contact);
    void messageReceived(ChatMessage *msg);
    void fileReceived(FileTransfer *tranfer);
    void contactStatusChanged(Contact *contact, Status *status);

    void stateUpdateReceived(Contact *contact, ChatSession::State state);

signals: // connection state
    void error();
   
    void connected();
    void disconnected();
    void accountSaved() const;

public slots:
    virtual void connectToServer() = 0;
    virtual void disconnectFromServer() = 0;

    virtual void sendMessage(ChatMessage *msg) = 0;
    virtual void sendStateUpdate(const Contact *contact, ChatSession::State state) = 0;

    virtual void initFileTransfer(FileTransfer *fileTransfer) = 0;

public slots:
    virtual void remove() = 0;
    virtual void save() const = 0;
    virtual void load() = 0;
    
    virtual void initAccount() = 0;
    
    virtual void acceptContact(Contact *contact);
    virtual void refuseContact(Contact *contact);
    
    virtual Contact *createContact(const QString &contactId) = 0;
    virtual void addContact(Contact *c);
    virtual void removeContact(Contact *c);

    virtual ChatSession *startSession(Contact *contact);
    virtual void endSession(ChatSession *session);
    
    virtual void installMessageHandler(MessageHandler *handler);
    virtual void removeMessageHandler(MessageHandler *handler);

protected slots:
    virtual void clearContacts();
    virtual void contactStatusChangedSlot(Status *status);

private:
    bool connectedStatus = false;
    bool active = true;

    QList<Contact*> m_contacts;
    QList<MessageHandler*> m_messageHandlers;
    QMap<QString, ChatSession*> m_chatSessions;
};

#endif // ACCOUNT_H
