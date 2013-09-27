#include "Contact.h"

Contact::Contact(Account *acc) : QObject(acc), account(acc)
{
}

Account *Contact::getAccount()
{
    return account;
}

QString Contact::getDisplayName() const
{
    return nickname;
}