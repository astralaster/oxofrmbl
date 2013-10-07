#include <QStringList>

#include <QDebug>

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
    return id();// + (m_resource.isEmpty() ? "" : "/"+m_resource);
}

QString XmppContact::id() const
{
    return parseJabberId(m_jid)[0] +"@"+ parseJabberId(m_jid)[1];
}

QStringList XmppContact::parseJabberId(const QString jid)
{
    QRegExp rxp("(.+)@(.+)/(.+)");

    if(!rxp.exactMatch(jid)) {
        rxp.setPattern("(.+)@(.+)");
    }

    rxp.indexIn(jid);

    return QStringList({rxp.cap(1), rxp.cap(2), rxp.cap(4)});
}

void XmppContact::setJid(const QString &jid)
{
    this->m_jid = jid;
}
