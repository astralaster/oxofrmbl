#include "XmppContact.h"
#include <QStringList>

XmppContact::XmppContact(const QString &name)
{
    QStringList jidParts = name.split("@");
    server = jidParts[1];
    user = jidParts[0];
}

XmppContact::XmppContact(const QString &server, const QString &user) :
    server(server), user(user)
{
}

