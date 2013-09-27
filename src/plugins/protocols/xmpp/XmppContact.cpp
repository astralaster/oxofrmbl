#include <QStringList>

#include <QDebug>

#include "XmppContact.h"

XmppContact::XmppContact(Account *acc, const QString &jid) : Contact(acc), jid(jid)
{
}

XmppContact::XmppContact(Account *acc, const QString &server, const QString &user) :
    XmppContact(acc, server+"@"+user)
{
}

QString XmppContact::getId() const
{
    return parseJabberId(jid)[0] +"@"+ parseJabberId(jid)[1];
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

