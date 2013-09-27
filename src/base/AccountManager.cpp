#include "AccountManager.h"

AccountManager::AccountManager(QObject *parent) : QObject(parent)
{
}

void AccountManager::addAccount(Account *a)
{
    accounts << a;
}

QList<Account *> AccountManager::getAccounts() const
{
    return accounts;
}