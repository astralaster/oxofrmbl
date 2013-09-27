#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QAbstractItemModel>

#include "common.h"
#include "Contact.h"

class ContactList : public QAbstractListModel
{
    Q_OBJECT
public:
    ContactList(Account *account);

    void addContact(Contact *contact);
    Contact *getContact(int index) const;

    Account *getAccount() const;


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void retrieveContacts();

private:
    Account *account;
    QList<Contact*> contacts = QList<Contact*>();
    
};

#endif // CONTACTLIST_H
