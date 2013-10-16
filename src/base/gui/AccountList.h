#ifndef ACCOUNTSLIST_H
#define ACCOUNTSLIST_H

#include <QObject>

#include <QAbstractListModel>

#include "common.h"

#include "base/AccountManager.h"
#include "base/Contact.h"

class AccountManager;

class AccountList : public QAbstractListModel
{
    Q_OBJECT
public:
    AccountList(AccountManager *manager);

    Account *accountAt(int index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void update();

private:
    AccountManager *m_manager = nullptr;

};

#endif // ACCOUNTSLIST_H
