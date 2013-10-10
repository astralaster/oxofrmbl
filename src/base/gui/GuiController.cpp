#include "GuiController.h"
#include "StatusIcon.h"

#include <QApplication>

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
    QObject(app), m_app(app)
{
    m_contactListWindow = new ContactListWindow(this);

    m_trayIcon = new QSystemTrayIcon(QIcon::fromTheme("user-available"), this);
    m_trayIcon->setVisible(true);

    m_trayIcon->setContextMenu(trayContextMenu());

    auto quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), m_contactListWindow);
    //quitShortcut->setContext(Qt::ApplicationShortcut);

    connect(quitShortcut, &QShortcut::activated, this, &GuiController::quit);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &GuiController::trayMenuTriggered);

    connect(m_contactListWindow, &ContactListWindow::statusChanged, app->accountManager(), &AccountManager::changeStatus);
    connect(m_contactListWindow, &ContactListWindow::statusChanged, this, &GuiController::changeStatusIcon);

    if(m_useTabs) {
        m_tabbedChatWindow = new TabbedChatWindow();
    }
}

void GuiController::show()
{
    m_contactListWindow->show();
}

void GuiController::quit()
{
    for(auto w: m_chatWindows.values()) {
        w->close();
    }
    
    emit exited();
}

void GuiController::startChat(ChatSession *session)
{
    auto window = new ChatWindow(session);
    m_chatWindows[session] = window;

    if(m_useTabs) {
        m_tabbedChatWindow->addTab(window);
    } else {
        window->showNormal();
    }
}

void GuiController::activateChat(ChatSession *session)
{
    if(m_useTabs) {
        m_tabbedChatWindow->activateChatWindow(m_chatWindows[session]);
    } else {
        m_chatWindows[session]->showNormal();
    }
}

void GuiController::changeStatusIcon(Status *status)
{
    auto icon = StatusIcon::forStatus(status);
    
    m_contactListWindow->setWindowIcon(icon);
    m_trayIcon->setIcon(icon);
}

void GuiController::showAccountsWindow()
{
    if(m_accountsWindow == nullptr) {
        m_accountsWindow = new AccountsWindow(m_app);
    }

    m_accountsWindow->setVisible(true);
}

void GuiController::showAboutDialog()
{
    QMessageBox::about(m_contactListWindow, "About Oxofrmbl", "Oxofrmbl (c) 2013 Sascha Pickel, Daniel Bräckelmann");
}

void GuiController::showAddContactDialog()
{
    auto dialog = new AddContactDialog(m_app->accountManager());
    
    if(dialog->exec() == QDialog::Accepted)
    {
        auto contactId = dialog->getId();
        auto account = dialog->getAccount();
        
        account->addContact(account->createContact(contactId));
    }
    
    delete dialog;
}

void GuiController::trayMenuTriggered(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
    {
        m_contactListWindow->setVisible(!m_contactListWindow->isVisible());
    }
    else if(reason == QSystemTrayIcon::Context)
    {
        // 
    } else {
        quit();
    }
}

void GuiController::handleError()
{
    //QMessageBox::critical(m_contactListWindow, "An error occured", "?");
}

void GuiController::addAccount(Account *account)
{
    connect(account, &Account::sessionStarted,   this, &GuiController::startChat);
    connect(account, &Account::sessionActivated, this, &GuiController::activateChat);
    
    connect(account, &Account::error, this, &GuiController::handleError);
    
    connect(this, &GuiController::exited, account, &Account::disconnectFromServer);
    connect(this, &GuiController::exited, m_app, &ApplicationController::quit);

    auto contactList = new ContactList(account, this);
    
    m_contactLists[account] = contactList;
    m_contactListWindow->addContactList(contactList);
}

void GuiController::removeAccount(Account *account)
{
    auto cl = m_contactLists.take(account);
    
    m_contactListWindow->removeContactList(cl);
    
    delete cl;
}

QMenu *GuiController::trayContextMenu() const
{
    QMenu *result = new QMenu();

    result->addAction(QIcon::fromTheme("help-about"), "About", this, SLOT(showAboutDialog()));
    result->addAction("Accounts", this, SLOT(showAccountsWindow()));
    result->addAction(QIcon::fromTheme("application-exit"), "Quit", this, SLOT(quit()));

    return result;
}
