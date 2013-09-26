#include "gui/ContactListWindow.h"

#include <QApplication>

#include "plugins/protocols/xmpp/XmppAccount.h"
#include "plugins/protocols/xmpp/XmppContact.h"

#include "ContactList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Account *account = new XmppAccount("jabber.ccc.de", "dc2_test", "blubbb");
    account->connectToServer();

    ContactList cl(account);

    ContactListWindow clw;
    clw.getList()->setModel(&cl);
    clw.show();

    a.connect(account, &Account::connected, &cl, &ContactList::retrieveContacts);

    a.connect(&clw, &ContactListWindow::windowClosed, account, &Account::disconnectFromServer);
    a.connect(&clw, &ContactListWindow::windowClosed, QApplication::exit);

    return a.exec();
}
