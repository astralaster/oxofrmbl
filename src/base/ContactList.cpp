#include "ContactList.h"

#include <QDebug>

ContactList::ContactList(Account *account) : account(account)
{

}

Contact *ContactList::getContact(int index) const
{
    return contacts[index];
}

int ContactList::rowCount(const QModelIndex &parent) const
{
    return contacts.count();
}

QVariant ContactList::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return contacts[index.row()]->getDisplayName();
    }

    return QVariant();
}

void ContactList::retrieveContacts()
{
    contacts.append(account->getContacts());

    emit dataChanged(index(0), index(0));
}
