#ifndef XMPPCONTACT_H
#define XMPPCONTACT_H

#include "Contact.h"

class XmppContact : public Contact
{
public:
    XmppContact(const Account *acc, const QString &name);
    XmppContact(const Account *acc, const QString &server, const QString &user);

    QString getDisplayName() const override {return getId();}

    QString getId() const {return user+"@"+server;}

private:
    QString server;
    QString user;
};

#endif // XMPPCONTACT_H
