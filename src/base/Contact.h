#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include "Account.h"

class Account;

class Contact : public QObject
{
    Q_OBJECT
public:
    Contact(const Account *acc);

    const Account *getAccount() const {return account;}

    virtual QString getId() const = 0;
    virtual QString getDisplayName() const {return nickname;}

protected:
    const Account *account;
    QString nickname;
    
};

#endif // CONTACT_H
