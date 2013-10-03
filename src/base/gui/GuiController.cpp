#include "GuiController.h"

#include <QApplication>
#include <QDebug>
#include <QShortcut>

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
    connect(trayIcon, &QSystemTrayIcon::activated, this, &GuiController::activateContactList);

    connect(clw, &ContactListWindow::statusChanged, app->getAccountManager(), &AccountManager::changeStatus);
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

void GuiController::activateContactList(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger) {
        clw->setVisible(!clw->isVisible());
    } else if(reason == QSystemTrayIcon::Context) {

    } else {
        emit quit();
    }
}

void GuiController::addAccount(Account *account)
{
    connect(account, &Account::sessionStarted,   this, &GuiController::startChat);
    connect(account, &Account::sessionActivated, this, &GuiController::activateChat);
    
    connect(this, &GuiController::quit, account, &Account::disconnectFromServer);
    connect(this, &GuiController::quit, app, &ApplicationController::quit);

    auto contactList = new ContactList(account, this);

    connect(account, &Account::connected, contactList, &ContactList::retrieveContacts);
    
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

    result->addAction("Accounts", this, SLOT(showAccountsWindow()));
    result->addAction(QIcon::fromTheme("application-exit"), "Quit", this, SIGNAL(quit()));

    return result;
}
