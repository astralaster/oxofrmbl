#ifndef CONTACTLISTWIDGET_H
#define CONTACTLISTWIDGET_H

#include <QListView>

#include "common.h"
#include "../ContactList.h"

class ContactListWidget : public QListView
{
    Q_OBJECT
public:
    explicit ContactListWidget(ContactList *cl, QWidget *parent = nullptr);
    
signals:
    void contactRemoved(Contact *contact);
    
public slots:
    void removeSelectedContact();
    void removeContactAtIndex(const QModelIndex &index);
    void openContactAtIndex(const QModelIndex &index);
    
protected slots:
    void keyPressEvent(QKeyEvent *event) override;
    
private:
    void generateContextMenu();

private:
    ContactList *contactList;

};

#endif // CONTACTLISTWIDGET_H
