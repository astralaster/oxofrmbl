#include "XmppPlugin.h"

#include "base/Account.h"
#include "XmppAccount.h"

#include "gui/XmppAccountWindow.h"

XmppPlugin::XmppPlugin(QObject *parent) :
    QObject(parent)
{
}

XmppAccount *XmppPlugin::createAccount()
{
    auto account = new XmppAccount();
    
    app->getAccountManager()->addAccount(new Account(account));
    
    return account;
}

void XmppPlugin::showAccountWindow(Account *account)
{
    (new XmppAccountWindow(this, dynamic_cast<XmppAccount*>(account->getAccountObject())))->show();
}

void XmppPlugin::init(ApplicationController *app)
{
    this->app = app;
}
