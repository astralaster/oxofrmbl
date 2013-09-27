#include "ContactListWindow.h"
#include "ui_ContactListWindow.h"

#include "ChatWindow.h"
#include "ContactList.h"
#include "Chat.h"

#include <QDebug>

ContactListWindow::ContactListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactListWindow)
{
    ui->setupUi(this);
}

ContactListWindow::~ContactListWindow()
{
    delete ui;
}

QListView *ContactListWindow::getList()
{
    return ui->contactList;
}

void ContactListWindow::closeEvent(QCloseEvent *e)
{
    emit windowClosed();
}

void ContactListWindow::on_contactList_doubleClicked(const QModelIndex &index)
{
    auto contact = dynamic_cast<ContactList*>(ui->contactList->model())->getContact(index.row());

    contact->getAccount()->startChat(contact);
}