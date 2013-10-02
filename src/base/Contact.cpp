#include "Contact.h"

#include <QDebug>

Contact::Contact(ContactInterface *contact, Account *acc) : Person(acc), contact(contact), account(acc)
{
}

QString Contact::getId() const
{
    return contact->getId();
}

QString Contact::getDisplayName() const
{
    return contact->getDisplayName();
}

Account *Contact::getAccount()
{
    return account;
}