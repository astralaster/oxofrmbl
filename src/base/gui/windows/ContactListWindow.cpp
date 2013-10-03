#include "ContactListWindow.h"
#include "ui_ContactListWindow.h"

#include <QDebug>
#include <QCloseEvent>

#include "gui/widgets/ContactListWidget.h"
#include "ChatWindow.h"
#include "base/ChatSession.h"

ContactListWindow::ContactListWindow(GuiController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactListWindow)
{
    ui->setupUi(this);

    connect(ui->actionAccounts, &QAction::triggered, controller, &GuiController::showAccountsWindow);
}

ContactListWindow::~ContactListWindow()
{
    delete ui;
}


QComboBox *ContactListWindow::getStatusSelect()
{
    return ui->status;
}

void ContactListWindow::addContactList(ContactList *cl)
{
    this->ui->contactListLayout->addWidget(new ContactListWidget(cl, ui->contactList));
}

void ContactListWindow::closeEvent(QCloseEvent *e)
{
    //setVisible(false);
    //e->ignore();
    //emit windowClosed();
}

void ContactListWindow::on_status_currentIndexChanged(int index)
{
    emit statusChanged((Account::Status)index);
}
