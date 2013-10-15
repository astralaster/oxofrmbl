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

    m_status = new Status();
    m_status->setType(Status::Online);

    auto quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), m_contactListWindow);
    //quitShortcut->setContext(Qt::ApplicationShortcut);
    
    QApplication::setQuitOnLastWindowClosed(false);

    connect(quitShortcut, &QShortcut::activated, this, &GuiController::quit);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &GuiController::trayMenuTriggered);

    connect(m_contactListWindow, &ContactListWindow::statusChanged, app->accountManager(), &AccountManager::changeStatus);
    connect(m_contactListWindow, &ContactListWindow::statusChanged, this, &GuiController::updateStatus);

    if(m_useTabs) {
        m_tabbedChatWindow = new TabbedChatWindow(this);
    }
}

ChatWindow *GuiController::chatWindowForSession(ChatSession *session)
{
    return m_chatWindows.contains(session) ? m_chatWindows[session] : nullptr;
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
    
    emit terminated();
}

void GuiController::startSession(ChatSession *session)
{
    auto window = new ChatWindow(session);//, m_contactListWindow);
    m_chatWindows[session] = window;

    connect(window, &ChatWindow::blink, this, &GuiController::toggleStatusIcon);

    if(m_useTabs)
    {
        m_tabbedChatWindow->addTab(window);
    } else
    {
        window->show();
    }
}

void GuiController::activateSession(ChatSession *session)
{
    if(m_useTabs)
    {
        m_tabbedChatWindow->activateChatWindow(m_chatWindows[session]);
    } else
    {
        m_chatWindows[session]->showNormal();
        m_chatWindows[session]->activateWindow();
    }
}

void GuiController::updateStatus(Status *status)
{
    m_status = status;
    updateStatusIcon(StatusIcon::forStatus(status));
}

void GuiController::updateStatusIcon(const QIcon &icon)
{
    m_contactListWindow->setWindowIcon(icon);
    m_trayIcon->setIcon(icon);
}

void GuiController::toggleStatusIcon(bool forceStatus)
{
    QIcon statusIcon = StatusIcon::forStatus(m_status);

    if(forceStatus || m_trayIcon->icon().name() != statusIcon.name()) {
        m_trayIcon->setIcon(statusIcon);
    } else {
        m_trayIcon->setIcon(QIcon::fromTheme("mail-message-new"));
    }
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
    if(m_app->accountManager()->accounts().isEmpty()) {
        return;
    }

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
    if(reason == QSystemTrayIcon::Trigger)
    {
        m_contactListWindow->setVisible(!m_contactListWindow->isVisible());
    }
    else if(reason == QSystemTrayIcon::Context || reason == QSystemTrayIcon::DoubleClick)
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

void GuiController::confirmContact(Contact *c)
{
    auto text = QString("Add %1 as your contact?").arg(c->displayName());
    
    if(QMessageBox::question(m_contactListWindow, "Contact request", text) == QMessageBox::Yes)
    {
        c->account()->acceptContact(c);
    } else {
        c->account()->refuseContact(c);
    }
}

void GuiController::addAccount(Account *account)
{
    connect(account, &Account::sessionStarted,   this, &GuiController::startSession);
    connect(account, &Account::sessionActivated, this, &GuiController::activateSession);
    
    connect(account, &Account::error, this, &GuiController::handleError);
    
    connect(account, &Account::contactRequestReceived, this, &GuiController::confirmContact);
    connect(account, &Account::statusChanged, this, &GuiController::updateStatus);

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
