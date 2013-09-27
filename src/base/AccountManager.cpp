#include "AccountManager.h"

AccountManager::AccountManager()
{
}

QList<Account *> AccountManager::getAccounts() const
{
    return accounts;
}