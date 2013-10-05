#include "Contact.h"

#include <QDebug>

#include "Account.h"

Contact::Contact(Account *acc) : Person(acc), account(acc)
{
}

Account *Contact::getAccount()
{
    return account;
}
