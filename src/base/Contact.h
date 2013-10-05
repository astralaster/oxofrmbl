#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include "common.h"
#include "Person.h"

class Contact : public Person
{
    Q_OBJECT
public:
    Contact(Account *acc);

    Account *getAccount();

protected:
    Account *account = nullptr;
    
};

#endif // CONTACT_H
