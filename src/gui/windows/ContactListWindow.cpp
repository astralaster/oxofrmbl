#include "ContactListWindow.h"
#include "ui_ContactListWindow.h"

#include <QDebug>
#include <QCloseEvent>

#include "ChatWindow.h"
#include "base/ChatSession.h"

ContactListWindow::ContactListWindow(ContactList *contacts, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactListWindow)
{
    ui->setupUi(this);

    ui->contactList->setModel(contacts);
}

ContactListWindow::~ContactListWindow()
{
    delete ui;
}


QComboBox *ContactListWindow::getStatusSelect()
{
    return ui->status;
}

void ContactListWindow::closeEvent(QCloseEvent *e)
{
    //setVisible(false);
    //e->ignore();
    //emit windowClosed();
}


void ContactListWindow::on_contactList_doubleClicked(const QModelIndex &index)
{
    auto contact = dynamic_cast<ContactList*>(ui->contactList->model())->getContact(index.row());

    contact->getAccount()->startSession(contact);
}

void ContactListWindow::on_status_currentIndexChanged(int index)
{
    emit statusChanged((Account::Status)index);
}
