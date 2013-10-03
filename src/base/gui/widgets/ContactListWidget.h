#ifndef CONTACTLISTWIDGET_H
#define CONTACTLISTWIDGET_H

#include <QListView>

#include "../ContactList.h"

class ContactListWidget : public QListView
{
    Q_OBJECT
public:
    explicit ContactListWidget(ContactList *cl, QWidget *parent = 0);
    
public slots:
    void openContact(const QModelIndex &index);

private:
    ContactList *contactList;

};

#endif // CONTACTLISTWIDGET_H
