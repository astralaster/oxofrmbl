#include "gui/ContactListWindow.h"

#include <QApplication>

#include "ContactList.h"

#include "plugins/protocols/xmpp/XmppAccount.h"
#include "plugins/protocols/xmpp/XmppContact.h"

#include "gui/GuiController.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto account = new XmppAccount("jabber.ccc.de", "dc2_test", "blubbb");
    account->connectToServer();

    ContactList cl(account);

    auto gui = new GuiController(&cl, &a);

    a.connect(gui, &GuiController::exitApp, account, &Account::disconnectFromServer);
    a.connect(gui, SIGNAL(exitApp()), SLOT(QApplication::exit()));

    a.connect(account, &Account::connected, &cl, &ContactList::retrieveContacts);

    return a.exec();
}
