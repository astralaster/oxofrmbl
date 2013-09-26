#include <QStringList>

#include "XmppContact.h"

XmppContact::XmppContact(const Account *acc, const QString &name) : XmppContact(acc, name.split("@")[1], name.split("@")[0])
{
    //QStringList jidParts = name.split("@");
    //server = jidParts[1];
    //user = jidParts[0];
}

XmppContact::XmppContact(const Account *acc, const QString &server, const QString &user) :
    Contact(acc),
    server(server), user(user)
{
}

