#include "ContactList.h"

#include <QDebug>

ContactList::ContactList(Account *account, QObject *parent) : 
    QAbstractListModel(parent), account(account)
{
    connect(account, &Account::connected, this, &ContactList::retrieveContacts);
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
    if (role == Qt::DisplayRole)
    {
        return account->getContacts()[index.row()]->getDisplayName();
    }

    return QVariant();
}

void ContactList::retrieveContacts()
{
    emit dataChanged(index(0), index(0));
}
