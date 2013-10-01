#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include "common.h"
#include "Person.h"
#include "Account.h"

class Contact : public Person
{
    Q_OBJECT
public:
    Contact(Account *acc = nullptr);
    ~Contact();

    virtual Account *getAccount();

protected:
    Account *account;
    
};

#endif // CONTACT_H
