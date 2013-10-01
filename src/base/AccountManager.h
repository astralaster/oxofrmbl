#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QAbstractListModel>
#include <QList>

#include "common.h"
#include "Account.h"

class AccountManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AccountManager(QObject *parent = 0);

    Account *getAccount(int index);
    QList<Account*> getAccounts() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void addAccount(Account *a);
    void changeStatus(Account::Status status);

    void save() const;
    void load();

private:
    QList<Account*> accounts;
};

#endif // ACCOUNTMANAGER_H
