#include "ContactListWidget.h"

#include "base/Account.h"
#include "base/Contact.h"
#include "gui/ContactList.h"

ContactListWidget::ContactListWidget(ContactList *cl, QWidget *parent) :
    QListView(parent), contactList(cl)
{
    this->setModel(cl);
    
    connect(this, &QListView::doubleClicked, this, &ContactListWidget::openContact);
}

void ContactListWidget::openContact(const QModelIndex &index)
{
    auto contact = contactList->getContact(index.row());

    contact->getAccount()->startSession(contact);
}