#include "ApplicationController.h"

#include <QApplication>
#include <QSettings>

#include "plugins/protocols/xmpp/XmppAccount.h"
#include "plugins/protocols/xmpp/XmppContact.h"
#include "plugins/protocols/xmpp/gui/XmppAccountWindow.h"

#include "gui/GuiController.h"

ApplicationController::ApplicationController(QObject *parent) :
    QObject(parent)
{
    QCoreApplication::setOrganizationName("oxofrmbl");
    QCoreApplication::setApplicationName("oxofrmbl");

    //qDebug() << account->metaObject()->className();

    accountManager = new AccountManager(this);
    accountManager->load();

    auto account = accountManager->getAccount(0);
    account->connectToServer();

    contactList = new ContactList(account);

    auto gui = new GuiController(this);

    connect(gui, &GuiController::quit, account, &Account::disconnectFromServer);
    connect(gui, &GuiController::quit, this, &ApplicationController::quit);

    connect(account, &Account::connected, contactList, &ContactList::retrieveContacts);
}

ContactList *ApplicationController::getContactList()
{
    return contactList;
}

AccountManager *ApplicationController::getAccountManager()
{
    return accountManager;
}
