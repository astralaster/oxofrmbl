#include "ContactListWidget.h"


#include <QKeyEvent>
#include <QAction>
#include <QMessageBox>

#include "base/Account.h"
#include "base/Contact.h"
#include "gui/ContactList.h"

ContactListWidget::ContactListWidget(ContactList *cl, QWidget *parent) :
    QListView(parent), contactList(cl)
{
    this->setModel(cl);
    
    setContextMenuPolicy(Qt::ActionsContextMenu);
    generateContextMenu();
    
    connect(this, &ContactListWidget::contactRemoved, cl, &ContactList::removeContact);
    connect(this, &QListView::doubleClicked, this, &ContactListWidget::openContactAtIndex);
}

void ContactListWidget::removeSelectedContact()
{
    removeContactAtIndex(currentIndex());
}

void ContactListWidget::removeContactAtIndex(const QModelIndex &index)
{
    auto contact = contactList->getContact(index.row());
    
    auto text = QString("Are you sure, that you want to delete %1?").arg(contact->id());
    
    if(QMessageBox::question(this, "Delete Contact", text) == QMessageBox::Yes) {
        emit contactRemoved(contact);
    }
}

void ContactListWidget::openContactAtIndex(const QModelIndex &index)
{
    auto contact = contactList->getContact(index.row());

    contact->account()->startSession(contact);
}

void ContactListWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete) {
        event->accept();
        removeSelectedContact();
        return;
    }
    
    event->ignore();
}

void ContactListWidget::generateContextMenu()
{
    QAction *removeContact = new QAction("Remove contact", this);
    connect(removeContact, &QAction::triggered, this, &ContactListWidget::removeSelectedContact);
    
    QList<QAction*> actions;
    actions << removeContact;
    
    addActions(actions);
}
