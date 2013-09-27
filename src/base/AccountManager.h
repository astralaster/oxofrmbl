#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QList>

#include "common.h"
#include "Account.h"

class AccountManager : public QObject
{
    Q_OBJECT
public:
    explicit AccountManager(QObject *parent = 0);

    void addAccount(Account *a);
    QList<Account*> getAccounts() const;

private:
    QList<Account*> accounts;
};

#endif // ACCOUNTMANAGER_H
