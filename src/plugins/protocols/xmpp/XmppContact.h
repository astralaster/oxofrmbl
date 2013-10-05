#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include <QString>

#include "base/Contact.h"

class XmppContact : public Contact
{
    Q_OBJECT
public:
    XmppContact(Account *account, const QString &jid);
    XmppContact(Account *account, const QString &server, const QString &user);

    QString getDisplayName() const override;
    QString getId() const;

    static QStringList parseJabberId(const QString jid);

public slots:
    void setJid(const QString &jid);

private:
    QString jid;
};

#endif // XMPPCONTACT_H
