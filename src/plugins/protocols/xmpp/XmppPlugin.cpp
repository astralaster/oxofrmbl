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


QXmppPresence &operator<<(QXmppPresence &presence, const Status &status)
{
    switch (status.getType())
    {
    case Status::Away:
        presence.setType(QXmppPresence::Available);
        presence.setAvailableStatusType(QXmppPresence::Away);
        break;

    case Status::Offline:
        presence = QXmppPresence::Unavailable;
        presence.setType(QXmppPresence::Unavailable);
        presence.setAvailableStatusType(QXmppPresence::Away);
        break;

    case Status::Online:
    default:
        presence.setType(QXmppPresence::Available);
        presence.setAvailableStatusType(QXmppPresence::Online);
        break;
    }
    
    return presence;
}


Status &operator<<(Status &status, const QXmppPresence &presence)
{
    switch (presence.type())
    {
    case QXmppPresence::Unavailable:
        status.setType(Status::Offline);
        break;

    case QXmppPresence::Available:
    default:
        switch(presence.availableStatusType())
        {
        case QXmppPresence::Away:
            status.setType(Status::Away);
            break;
            
        case QXmppPresence::Online:
        default:
            status.setType(Status::Online);
            break;
        }

        break;
    }
    
    return status;
}
