#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include <QString>

#include "XmppAccount.h"
#include "interfaces/ContactInterface.h"

class XmppContact : public QObject, public ContactInterface
{
    Q_OBJECT
    Q_INTERFACES(ContactInterface)
public:
    XmppContact();
    XmppContact(const QString &jid);
    XmppContact(const QString &server, const QString &user);

    QString getDisplayName() const override;
    QString getId() const;

    static QStringList parseJabberId(const QString jid);

public slots:
    void setJid(const QString &jid);

private:
    QString jid;
};

#endif // XMPPCONTACT_H
