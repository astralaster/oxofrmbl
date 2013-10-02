#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include "common.h"
#include "Person.h"
#include "Account.h"

#include "interfaces/ContactInterface.h"

class Contact : public Person
{
    Q_OBJECT
public:
    Contact(ContactInterface *contact, Account *acc);

    QString getId() const override;
    QString getDisplayName() const override;

    Account *getAccount();

protected:
    ContactInterface *contact;
    Account *account;
    
};

#endif // CONTACT_H
