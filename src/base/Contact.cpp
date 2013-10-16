#include "Contact.h"

#include "Account.h"

Contact::Contact(Account *acc) : Contact(acc, "")
{
}

Contact::Contact(Account *acc, const QString &id, QObject *parent) :
    Person(id, acc), m_account(acc)
{
    
}

Contact::~Contact()
{
    qDebug() << "~Contact";
}

Account *Contact::account()
{
    return m_account;
}
