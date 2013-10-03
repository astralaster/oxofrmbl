#include <QStringList>

#include <QDebug>

#include "XmppContact.h"

XmppContact::XmppContact(const QString &jid) :
    jid(jid)
{
}

XmppContact::XmppContact(const QString &server, const QString &user) :
    XmppContact(server+"@"+user)
{
}

QString XmppContact::getDisplayName() const
{
    return getId();
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

void XmppContact::setJid(const QString &jid)
{
    this->jid = jid;
}

void XmppContact::setStatus(PersonInterface::Status status)
{

}

