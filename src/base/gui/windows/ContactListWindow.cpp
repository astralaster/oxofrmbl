#include "ContactListWindow.h"
#include "ui_ContactListWindow.h"


#include <QCloseEvent>

#include "ChatWindow.h"
#include "base/ChatSession.h"
#include "base/Status.h"

#include "gui/GuiController.h"
#include "gui/widgets/ContactListWidget.h"

ContactListWindow::ContactListWindow(GuiController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactListWindow)
{
    ui->setupUi(this);

    connect(ui->actionAccounts,   &QAction::triggered, controller, &GuiController::showAccountsWindow);
    connect(ui->actionAddContact, &QAction::triggered, controller, &GuiController::showAddContactDialog);
    connect(ui->actionAbout,      &QAction::triggered, controller, &GuiController::showAboutDialog);
}

ContactListWindow::~ContactListWindow()
{
    delete ui;
}

void ContactListWindow::addContactList(ContactList *cl)
{
    auto widget = new ContactListWidget(cl, ui->contactList);
    
    contactLists[cl] = widget;
    
    this->ui->contactListLayout->addWidget(widget);
}

void ContactListWindow::removeContactList(ContactList *cl)
{
    auto widget = contactLists.take(cl);
    this->ui->contactListLayout->removeWidget(widget);
    
    delete widget;
}

void ContactListWindow::contextMenuEvent(QContextMenuEvent *e)
{
    ui->menuContacts->exec(e->globalPos());
}

void ContactListWindow::closeEvent(QCloseEvent *e)
{
    setVisible(false);
    e->ignore();
    //emit windowClosed();
}

void ContactListWindow::on_status_currentIndexChanged(int index)
{
    auto status = new Status();
    status->setType(Status::Type(index));
    
    emit statusChanged(status);
}

