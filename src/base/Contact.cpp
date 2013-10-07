#include "Contact.h"

#include <QDebug>

#include "Account.h"

Contact::Contact(Account *acc) : Contact(acc, "")
{
}

Contact::Contact(Account *acc, const QString &id, QObject *parent) : Person(id, acc), m_account(acc)
{
    
}

Account *Contact::account()
{
    return m_account;
}
