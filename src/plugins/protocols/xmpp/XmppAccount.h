#ifndef XMPPACCOUNT_H
#define XMPPACCOUNT_H

#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>
#include <qxmpp/QXmppRosterManager.h>

#include "Account.h"

class XmppAccount : public Account
{
public:
    XmppAccount(const QString &server, const QString &user, const QString &password);
    ~XmppAccount();

    QList<Contact*> getContacts() const;

public slots:
    virtual bool connectToServer() override;
    virtual void disconnectFromServer() override;
    virtual void sendMessage(const ChatMessage *msg) override;

private slots:
    void connectedSlot();
    void messageReceivedSlot(const QXmppMessage &message);

private:
    QXmppClient *client;
    QString server, user, password;
};

#endif // XMPPACCOUNT_H
