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
    QCoreApplication::setOrganizationName("kfnnmpa");
    QCoreApplication::setApplicationName("oxofrmbl");

    auto account = new XmppAccount("jabber.ccc.de", "dc2_test", "blubbb");
    account->connectToServer();

    //qDebug() << account->metaObject()->className();

    accountManager = new AccountManager(this);
    accountManager->addAccount(account);

    contactList = new ContactList(account);

    auto gui = new GuiController(this);

    connect(gui, &GuiController::quit, account, &Account::disconnectFromServer);
    connect(gui, &GuiController::quit, this, &ApplicationController::quit);

    //connect(account, &Account::connected, contactList, &ContactList::retrieveContacts);
}

ContactList *ApplicationController::getContactList()
{
    return contactList;
}

AccountManager *ApplicationController::getAccountManager()
{
    return accountManager;
}
