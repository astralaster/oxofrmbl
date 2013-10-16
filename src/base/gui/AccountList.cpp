#include "AccountList.h"

AccountList::AccountList(AccountManager *manager) :
    QAbstractListModel(manager), m_manager(manager)

{
    connect(manager, &AccountManager::accountAdded, this, &AccountList::update);
    connect(manager, &AccountManager::accountRemoved, this, &AccountList::update);
    connect(manager, &AccountManager::changed, this, &AccountList::update);
}

int AccountList::rowCount(const QModelIndex &parent) const
{
    return m_manager->accounts().count();
}

QVariant AccountList::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return accountAt(index.row())->displayName();
    }

    return QVariant();
}

void AccountList::update()
{
    emit dataChanged(index(0), index(0));
}

Account *AccountList::accountAt(int index) const
{
    return m_manager->accounts()[index];
}
