#ifndef XMPPACCOUNT_H
#define XMPPACCOUNT_H

#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>
#include <qxmpp/QXmppRosterManager.h>

#include "base/Account.h"

class XmppAccount : public Account
{
    Q_OBJECT
public:
    XmppAccount(const QString &server = "", const QString &user = "", const QString &password = "");
    ~XmppAccount();

    QString getServer() const;
    QString getUser() const;
    QString getPassword() const;
    QString getResource() const;

    QString getId() const override;

public slots:
    bool connectToServer() override;
    void disconnectFromServer() override;
    void sendMessage(const ChatMessage *msg) override;

    void setState(const QString &server, const QString &user, const QString &password, const QString &resource);
    void setServer(const QString &server);
    void setUser(const QString &user);
    void setPassword(const QString &password);
    void setResource(const QString &resource);

    void setStatus(Account::Status status) override;

    void retrieveContacts();
    void clearContacts();

    void save() const override;
    void load() override;

private slots:
    void messageReceivedSlot(const QXmppMessage &message);

private:
    QXmppClient *client;
    QString server, user, password, resource;
};

#endif // XMPPACCOUNT_H
