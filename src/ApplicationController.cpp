#include "ApplicationController.h"

#include "plugins/protocols/xmpp/XmppAccount.h"
#include "plugins/protocols/xmpp/XmppContact.h"

#include "ContactList.h"

ApplicationController::ApplicationController(int argc, char *argv[]) : a(argc, argv)
{
    /*Account *account = new XmppAccount("jabber.ccc.de", "dc2_test", "blubbb");
    account->connectToServer();
    ContactList cl;
    cl.addContact(new XmppContact(account, "dc2@jabber.ccc.de"));

    clw.getList()->setModel(&cl);
    clw.show();

    connect(&a, &QGuiApplication::lastWindowClosed, account, &Account::disconnectFromServer);
    connect(&clw, &ContactListWindow::windowClosed, &QApplication::exit);*/
}

int ApplicationController::exec()
{
    /*clw.show();
    return a.exec();*/
}