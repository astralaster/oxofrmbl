#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QAbstractListModel>
#include <QList>

#include "common.h"

#include "ApplicationController.h"
#include "Account.h"
class ApplicationController;

class AccountManager : public QObject
{
    Q_OBJECT
public:
    explicit AccountManager(ApplicationController *app);

    Account *account(int index);
    QList<Account*> accounts() const;


signals:
    void changed(bool saveData);
    void accountRemoved(Account *account);
    void accountAdded(Account *account);

public slots:
    void dataChangedSlot(bool save);
    
    void connectAccounts();
    void disconnectAccounts();
    
    void addAccount(Account *account, bool saveData = false);
    void removeAccount(Account *account);
    void changeStatus(Status *status);

    void save() const;
    void load();

private:
    ApplicationController *m_app = nullptr;
    QList<Account*> m_accounts;
};

#endif // ACCOUNTMANAGER_H
