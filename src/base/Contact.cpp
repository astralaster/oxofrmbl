#include "Contact.h"

#include <QDebug>

Contact::Contact(Account *acc) : Person(acc), account(acc)
{
}

Contact::~Contact()
{
}

Account *Contact::getAccount()
{
    return account;
}