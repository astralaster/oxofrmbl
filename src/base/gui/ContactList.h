#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QAbstractItemModel>

#include "common.h"

#include "base/Account.h"
#include "base/Contact.h"

class ContactList : public QAbstractListModel
{
    Q_OBJECT
public:
    ContactList(Account *account, QObject *parent);

    Contact *getContact(int index) const;
    Account *getAccount() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    //void addContact(Contact *contact);
    void removeContact(Contact *contact);
    //void removeContactAtIndex(int index);
    //void clearContacts();
    //void retrieveContacts();
    //void updateContactStatus(Contact *contact, Status *status);
    
    void update();


private:
    Account *account = nullptr;
    
};

#endif // CONTACTLIST_H
