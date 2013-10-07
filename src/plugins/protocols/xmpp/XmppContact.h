#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include <QString>

#include "base/Contact.h"

class XmppContact : public Contact
{
    Q_OBJECT
public:
    XmppContact(Account *account, const QString &jid);
    XmppContact(Account *account, const QString &jid, const QList<QString> &resources);
    QString displayName() const override;
    QString id() const;

    static QStringList parseJabberId(const QString jid);

public slots:
    void setJid(const QString &jid);

private:
    QString m_jid;
    QList<QString> m_resources;
};

#endif // XMPPCONTACT_H
