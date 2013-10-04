#include "Contact.h"

#include <QDebug>

Contact::Contact(Account *acc) : Person(acc), account(acc)
{
}

/*QString Contact::getId() const
{
    return contact->getId();
}

QString Contact::getDisplayName() const
{
    return contact->getDisplayName();
}*/

Account *Contact::getAccount()
{
    return account;
}
