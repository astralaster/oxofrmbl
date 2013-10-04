#ifndef XMPPACCOUNT_H
#define XMPPACCOUNT_H

#include <QString>

#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>
#include <qxmpp/QXmppRosterManager.h>

#include "base/Account.h"

class XmppAccount : public Account
{
    Q_OBJECT
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

public slots:
    bool connectToServer() override;
    void disconnectFromServer() override;
    void sendMessage(const ChatMessage *msg) override;

    void retrieveContacts();

    void remove() override;
    void save() const override;
    void load() override;
    
public slots:
    void setState(const QString &server, const QString &user, const QString &password, const QString &resource);
    void setServer(const QString &server);
    void setUser(const QString &user);
    void setPassword(const QString &password);
    void setResource(const QString &resource);
    
    void setAccountObject(Account *account);
    void setStatus(Status *status);
    

private slots:
    void presenceReceivedSlot(const QXmppPresence &presence);
    void messageReceivedSlot(const QXmppMessage &message);

private:
    QXmppClient *client = nullptr;
    QString server, user, password, resource;
};


#endif // XMPPACCOUNT_H
