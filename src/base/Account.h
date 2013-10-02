#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>
#include <QString>

#include "interfaces/AccountInterface.h"

#include "common.h"
#include "ChatMessage.h"
#include "Contact.h"

class Account : public Person
{
    Q_OBJECT
public:
    explicit Account(AccountInterface *account = nullptr, QObject *parent = 0);
    ~Account();

    void initAccount();

    ChatSession *getSession(const QString &contactId);

    QMap<QString, ChatSession*> getSessions();
    QList<Contact*> getContacts();

    QString getType() const;
    QString getId() const;
    QString getDisplayName() const;
    Status getStatus() const;

    void setId(const QString &id);

    bool isActive() const;

signals:
    void sessionStarted(ChatSession *session);
    void sessionActivated(ChatSession *session);
    void messageReceived(const ChatMessage *msg);
    void connected();
    void disconnected();

public slots:
    bool connectToServer();
    void disconnectFromServer();
    void sendMessage(const ChatMessage *msg);

    void addContact(Contact *contact);

    void setStatus(Status status);
    void setAccountObject(AccountInterface *account);

    ChatSession *startSession(Contact *contact);
    void endSession(ChatSession *session);

    void save() const;
    void load();

protected:
    AccountInterface *account;
    QString accountId;

    bool active = true;

    QList<Contact*> contacts;
    QMap<QString, ChatSession*> chatSessions;
};

#endif // ACCOUNT_H
