#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include "common.h"
#include "Person.h"
#include "Account.h"

class Account;

class Contact : public Person
{
    Q_OBJECT
public:
    explicit Contact(Account *acc);
    explicit Contact(Account *acc, const QString &m_id, QObject *parent = nullptr);
    ~Contact();

    Account *account();


private:
    Account *m_account = nullptr;
    
};

#endif // CONTACT_H
