#include "ContactList.h"

#include <QIcon>


#include "base/Account.h"
#include "base/Contact.h"
#include "base/Status.h"
#include "StatusIcon.h"

ContactList::ContactList(Account *account, QObject *parent) : 
    QAbstractListModel(parent), m_account(account)
{

    connect(account, &Account::connected, this, &ContactList::update);
    connect(account, &Account::disconnected, this, &ContactList::update);
    connect(account, &Account::contactAdded, this, &ContactList::update);
    connect(account, &Account::contactRemoved, this, &ContactList::update);
    
    connect(account, &Account::contactStatusChanged, this, &ContactList::update);
}

Contact *ContactList::contactAt(int index) const
{
    return m_account->contacts()[index];
}

Account *ContactList::account() const
{
    return m_account;
}

int ContactList::rowCount(const QModelIndex &parent) const
{
    return m_account->contacts().count();
}

QVariant ContactList::data(const QModelIndex &index, int role) const
{
    if(index.row() >= m_account->contacts().size()) {
        return QVariant();
    }
    
    auto contact = m_account->contacts()[index.row()];
    
    switch (role) {
    case Qt::DisplayRole:
        return contact->displayName();
        break;
        
    case Qt::DecorationRole:
        return StatusIcon::forStatus(contact->status());
        break;
        
    default:
        return QVariant();
        break;
    }
}

void ContactList::removeContact(Contact *contact)
{
    m_account->removeContact(contact);
}

void ContactList::update()
{
    emit dataChanged(index(0), index(0));
}
