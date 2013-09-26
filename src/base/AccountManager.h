#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QList>

#include "Account.h"

class AccountManager
{
public:
    AccountManager();

    void addAccount(Account *a);
    QList<Account*> getAccounts() const {return accounts;}

private:
    QList<Account*> accounts;
};

#endif // ACCOUNTMANAGER_H
