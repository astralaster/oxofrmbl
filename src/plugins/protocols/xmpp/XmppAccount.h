#ifndef XMPPACCOUNT_H
#define XMPPACCOUNT_H

#include <QString>

#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>

#include "base/Account.h"

class XmppAccount : public Account
{
    Q_OBJECT
public:
    XmppAccount();
    //XmppAccount(Account *account, const QString &server = "", const QString &user = "", const QString &password = "");
    ~XmppAccount();

    void initAccount();

    QString server() const;
    QString user() const;
    QString password() const;
    QString resource() const;

    QString type() const override;
    QString id() const override;
    QString displayName() const override;

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
    
    void setStatus(Status *status) override;
    
    Contact *createContact(const QString &contactId) override;
    void addContact(Contact *contact) override;
    void removeContact(Contact *contact) override;
    

private slots:
    void clearContacts();
    void presenceReceivedSlot(const QXmppPresence &presence);
    void messageReceivedSlot(const QXmppMessage &message);

private:
    QXmppClient *m_client = nullptr;
    QString m_server, m_user, m_password, m_resource;
};


#endif // XMPPACCOUNT_H
