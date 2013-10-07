#include "GuiController.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

#include "ContactList.h"
#include "base/ApplicationController.h"
#include "base/Contact.h"
#include "base/Account.h"
#include "base/AccountManager.h"
#include "base/Status.h"
#include "base/ChatSession.h"

#include "windows/ContactListWindow.h"
#include "windows/ChatWindow.h"
#include "windows/AccountsWindow.h"
#include "windows/AddContactDialog.h"

GuiController::GuiController(ApplicationController *app) :
    QObject(app), app(app)
{
    clw = new ContactListWindow(this);

    auto trayIcon = new QSystemTrayIcon(QIcon::fromTheme("user-available"), this);
    trayIcon->setVisible(true);

    trayIcon->setContextMenu(trayContextMenu());

    auto quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), clw);
    //quitShortcut->setContext(Qt::ApplicationShortcut);

    connect(quitShortcut, &QShortcut::activated, this, &GuiController::quit);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &GuiController::trayMenuTriggered);

    connect(clw, &ContactListWindow::statusChanged, app->accountManager(), &AccountManager::changeStatus);
}

void GuiController::show()
{
    clw->show();
}

void GuiController::startChat(ChatSession *session)
{
    auto cw = new ChatWindow(session);
    chatWindows[session] = cw;

    cw->show();
}

void GuiController::activateChat(ChatSession *session)
{
    ChatWindow *cw = chatWindows[session];

    cw->showNormal();
    cw->activateWindow();
}

void GuiController::showAccountsWindow()
{
    if(aw == nullptr) {
        aw = new AccountsWindow(app);
    }

    aw->setVisible(true);
}

void GuiController::showAboutDialog()
{
    QMessageBox::about(clw, "About Oxofrmbl", "Oxofrmbl (c) 2013 Sascha Pickel, Daniel Bräckelmann");
}

void GuiController::showAddContactDialog()
{
    auto dialog = new AddContactDialog(app->accountManager());
    
    if(dialog->exec() == QDialog::Accepted) {
        auto contactId = dialog->getId();
        auto account = dialog->getAccount();
        
        account->addContact(account->createContact(contactId));
    }
    
    delete dialog;
}

void GuiController::trayMenuTriggered(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        clw->setVisible(!clw->isVisible());
    } else if(reason == QSystemTrayIcon::Context) {

    } else {
        emit quit();
    }
}

void GuiController::handleError()
{
    //QMessageBox::critical(clw, "An error occured", "bla");
}

void GuiController::addAccount(Account *account)
{
    connect(account, &Account::sessionStarted,   this, &GuiController::startChat);
    connect(account, &Account::sessionActivated, this, &GuiController::activateChat);
    
    connect(account, &Account::error, this, &GuiController::handleError);
    
    connect(this, &GuiController::quit, account, &Account::disconnectFromServer);
    connect(this, &GuiController::quit, app, &ApplicationController::quit);

    auto contactList = new ContactList(account, this);
    
    contactLists[account] = contactList;
    clw->addContactList(contactList);
}

void GuiController::removeAccount(Account *account)
{
    auto cl = contactLists.take(account);
    
    clw->removeContactList(cl);
    
    delete cl;
}

QMenu *GuiController::trayContextMenu() const
{
    QMenu *result = new QMenu();

    result->addAction(QIcon::fromTheme("help-about"), "About", this, SLOT(showAboutDialog()));
    result->addAction("Accounts", this, SLOT(showAccountsWindow()));
    result->addAction(QIcon::fromTheme("application-exit"), "Quit", this, SIGNAL(quit()));
    
    

    return result;
}
