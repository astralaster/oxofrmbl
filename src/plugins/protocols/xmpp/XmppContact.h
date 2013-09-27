#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include "Contact.h"

class XmppContact : public Contact
{
public:
    XmppContact(Account *acc, const QString &jid);
    XmppContact(Account *acc, const QString &server, const QString &user);

    QString getDisplayName() const override;
    QString getId() const;

    static QStringList parseJabberId(const QString jid);

private:
    QString jid;
};

#endif // XMPPCONTACT_H
