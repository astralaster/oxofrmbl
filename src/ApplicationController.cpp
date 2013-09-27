#include "ApplicationController.h"


#include "plugins/protocols/xmpp/XmppAccount.h"
#include "plugins/protocols/xmpp/XmppContact.h"

#include "gui/GuiController.h"

ApplicationController::ApplicationController(QObject *parent) :
    QObject(parent), accountManager(this)
{
    auto account = new XmppAccount("jabber.ccc.de", "dc2_test", "blubbb");
    account->connectToServer();

    accountManager.addAccount(account);

    ContactList *cl = new ContactList(account);

    auto gui = new GuiController(cl, this);

    connect(gui, &GuiController::exitApp, account, &Account::disconnectFromServer);
    connect(gui, SIGNAL(exitApp()), SLOT(QApplication::exit()));

    connect(account, &Account::connected, cl, &ContactList::retrieveContacts);
}
