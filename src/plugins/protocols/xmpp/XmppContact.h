#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include "XmppAccount.h"
#include "interfaces/ContactInterface.h"

class XmppContact : public QObject, public ContactInterface
{
    Q_INTERFACES(ContactInterface)
    Q_PLUGIN_METADATA(IID "com.oxofrmbl/protocols/xmpp/contact")
public:
    XmppContact(const QString &jid);
    XmppContact(const QString &server, const QString &user);

    QString getDisplayName() const override;
    QString getId() const;

    static QStringList parseJabberId(const QString jid);

public slots:
    void setStatus(Status status) override;

private:
    QString jid;
};

#endif // XMPPCONTACT_H
