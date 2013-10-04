#include "XmppPlugin.h"

#include "base/Account.h"
#include "XmppAccount.h"

#include "gui/XmppAccountWindow.h"

XmppPlugin::XmppPlugin(QObject *parent) :
    QObject(parent)
{
}

Account *XmppPlugin::createAccount()
{
    qDebug() << "create account";
    return new XmppAccount();
}

void XmppPlugin::showAccountWindow(Account *account)
{
    (new XmppAccountWindow(this, dynamic_cast<XmppAccount*>(account)))->show();
}

void XmppPlugin::init(ApplicationController *app)
{

    this->app = app;
}
