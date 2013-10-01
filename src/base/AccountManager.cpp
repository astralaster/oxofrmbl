#include "AccountManager.h"

#include <QDebug>

AccountManager::AccountManager(QObject *parent) : QAbstractListModel(parent)
{
}

Account *AccountManager::getAccount(int index)
{
    return accounts[index];
}

void AccountManager::addAccount(Account *a)
{
    accounts << a;
    emit dataChanged(index(accounts.size()-1),index(accounts.size()-1));
}

QList<Account*> AccountManager::getAccounts() const
{
    return accounts;
}

int AccountManager::rowCount(const QModelIndex &parent) const
{
    /*int result = 0;

    for(auto a : accounts) {
        result += a->getContacts()->count();
    }

    return result;*/
    return accounts.count();
}

QVariant AccountManager::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return accounts[index.row()]->getDisplayName();
    }

    return QVariant();
}

void AccountManager::changeStatus(Person::Status status)
{
    for(auto a : accounts) {
        a->setStatus(status);
    }
}

void AccountManager::save() const
{
    //QStringList list;

    /*QString key = QString("accounts/list/%1");

    for(auto a: accounts) {
        QSettings().setValue(key.arg("server"), server);
    }*/
}

void AccountManager::load()
{

}