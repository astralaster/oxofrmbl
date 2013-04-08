#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include "ChatContact.h"

class XmppContact : public ChatContact
{
public:
    XmppContact(const QString &name);
    XmppContact(const QString &server, const QString &user);
    virtual QString getId() const {return user+"@"+server;}

private:
    QString server;
    QString user;
};

#endif // XMPPCONTACT_H
