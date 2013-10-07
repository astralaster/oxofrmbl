#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QAbstractListModel>
#include <QList>

#include "common.h"

#include "ApplicationController.h"
#include "Account.h"
class ApplicationController;

class AccountManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AccountManager(ApplicationController *app, QObject *parent = nullptr);

    Account *account(int index);
    QList<Account*> accounts() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
signals:
    void changed(bool saveData);
    void accountRemoved(Account *account);
    void accountAdded(Account *account);

public slots:
    void accountSavedSlot();
    void dataChangedSlot(bool save);
    
    void connectAccounts();
    
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
