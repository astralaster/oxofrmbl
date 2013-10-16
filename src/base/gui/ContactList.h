#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QAbstractListModel>

#include "common.h"

#include "base/Account.h"
#include "base/Contact.h"

class ContactList : public QAbstractListModel
{
    Q_OBJECT
public:
    ContactList(Account *account, QObject *parent);

    Contact *contactAt(int index) const;
    Account *account() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void removeContact(Contact *contact);
    void update();

private:
    Account *m_account = nullptr;
    
};

#endif // CONTACTLIST_H
