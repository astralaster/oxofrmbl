#ifndef XMPPACCOUNT_H
#define XMPPACCOUNT_H

#include <QString>

#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>
#include <qxmpp/QXmppRosterManager.h>

#include "base/ChatMessage.h"

#include "interfaces/AccountInterface.h"

class XmppAccount : public QObject, public AccountInterface
{
    Q_OBJECT
    Q_INTERFACES(AccountInterface)
public:
    XmppAccount();
    //XmppAccount(Account *account, const QString &server = "", const QString &user = "", const QString &password = "");
    ~XmppAccount();

    void initAccount();

    QString getServer() const;
    QString getUser() const;
    QString getPassword() const;
    QString getResource() const;

    QString getType() const override;
    QString getId() const override;
    QString getDisplayName() const override;
    Account *getAccountObject() override;

    void setAccountObject(Account *account);

signals:
    void messageReceived(const ChatMessage *msg);
    void connected();
    void disconnected();

public slots:
    bool connectToServer() override;
    void disconnectFromServer() override;
    void sendMessage(const ChatMessage *msg) override;

    void setState(const QString &server, const QString &user, const QString &password, const QString &resource);
    void setServer(const QString &server);
    void setUser(const QString &user);
    void setPassword(const QString &password);
    void setResource(const QString &resource);

    void setStatus(Status status) override;

    void retrieveContacts();

    void save() const override;
    void load() override;

private slots:
    void messageReceivedSlot(const QXmppMessage &message);

private:
    Account *account;

    QXmppClient *client;
    QString server, user, password, resource;
};


#endif // XMPPACCOUNT_H
