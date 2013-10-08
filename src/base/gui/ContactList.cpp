#include "ContactList.h"

#include <QIcon>


#include "base/Account.h"
#include "base/Contact.h"
#include "base/Status.h"
#include "StatusIcon.h"

ContactList::ContactList(Account *account, QObject *parent) : 
    QAbstractListModel(parent), account(account)
{
    /*connect(account, &Account::connected, this, &ContactList::retrieveContacts);
    connect(account, &Account::disconnected, this, &ContactList::clearContacts);
    connect(account, &Account::contactAdded, this, &ContactList::addContact);
    connect(account, &Account::contactRemoved, this, &ContactList::removeContact);
    
    connect(account, &Account::contactStatusChanged, this, &ContactList::updateContactStatus);*/
    
    connect(account, &Account::connected, this, &ContactList::update);
    connect(account, &Account::disconnected, this, &ContactList::update);
    connect(account, &Account::contactAdded, this, &ContactList::update);
    connect(account, &Account::contactRemoved, this, &ContactList::update);
    
    connect(account, &Account::contactStatusChanged, this, &ContactList::update);
}

Contact *ContactList::getContact(int index) const
{
    return account->contacts()[index];
}

Account *ContactList::getAccount() const
{
    return account;
}

int ContactList::rowCount(const QModelIndex &parent) const
{
    return account->contacts().count();
}

QVariant ContactList::data(const QModelIndex &index, int role) const
{
    if(index.row() >= account->contacts().size()) {
        return QVariant();
    }
    
    auto contact = account->contacts()[index.row()];
    
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
    account->removeContact(contact);
    update();
}

void ContactList::update()
{
    emit dataChanged(index(0), index(0));
}

/*
void ContactList::addContact(Contact *contact)
{
    emit dataChanged(index(0), index(0));
}

void ContactList::removeContact(Contact *contact)
{
    //account->removeContact(contact);
    emit dataChanged(index(0), index(0));
}

void ContactList::removeContactAtIndex(int index)
{
    removeContact(account->getContacts()[index]);
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
}*/
