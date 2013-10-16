#include <QStringList>

#include "XmppContact.h"

XmppContact::XmppContact(Account *account, const QString &jid) :
    XmppContact(account, jid, QList<QString>())
{
}

XmppContact::XmppContact(Account *account, const QString &jid, const QList<QString> &resources) : 
    Contact(account), m_jid(jid), m_resources(resources)
{
}

QString XmppContact::displayName() const
{
    return id();
}

QString XmppContact::id() const
{
    return m_jid;
}

void XmppContact::addResource(const QString &resource)
{
    m_resources << resource;
}

void XmppContact::setJid(const QString &jid)
{
    this->m_jid = jid;
}
