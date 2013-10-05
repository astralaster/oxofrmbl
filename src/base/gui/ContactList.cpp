#include "ContactList.h"

#include <QIcon>

#include "base/Account.h"
#include "base/Contact.h"
#include "base/Status.h"
#include "StatusIcon.h"

ContactList::ContactList(Account *account, QObject *parent) : 
    QAbstractListModel(parent), account(account)
{
    connect(account, &Account::connected, this, &ContactList::retrieveContacts);
    connect(account, &Account::disconnected, this, &ContactList::clearContacts);
    
    connect(account, &Account::contactStatusChanged, this, &ContactList::updateContactStatus);
}

Contact *ContactList::getContact(int index) const
{
    return account->getContacts()[index];
}

Account *ContactList::getAccount() const
{
    return account;
}

int ContactList::rowCount(const QModelIndex &parent) const
{
    return account->getContacts().count();
}

QVariant ContactList::data(const QModelIndex &index, int role) const
{
    Contact *contact = account->getContacts()[index.row()];
    
    switch (role) {
    case Qt::DisplayRole:
        return contact->getDisplayName();
        break;
        
    case Qt::DecorationRole:
        return StatusIcon::forStatus(contact->getStatus());
        break;
        
    default:
        return QVariant();
        break;
    }
}

void ContactList::updateContactStatus(Contact *contact, Status *status)
{
    emit dataChanged(index(0), index(0));
}

void ContactList::clearContacts()
{
    emit dataChanged(index(0), index(0));
}

void ContactList::retrieveContacts()
{
    emit dataChanged(index(0), index(0));
}
