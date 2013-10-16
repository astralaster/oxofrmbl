#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include <QString>
#include <QSet>

#include "base/Contact.h"

class XmppContact : public Contact
{
    Q_OBJECT
public:
    XmppContact(Account *account, const QString &jid);
    XmppContact(Account *account, const QString &jid, const QList<QString> &resources);
    QString displayName() const override;
    QString id() const;

public slots:
    void addResource(const QString &resource);
    void setJid(const QString &jid);

private:
    QString m_jid;
    QList<QString> m_resources;
};

#endif // XMPPCONTACT_H
