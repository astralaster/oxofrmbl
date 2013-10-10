#include "XmppPlugin.h"

#include "XmppAccount.h"

#include "base/Account.h"
#include "base/Status.h"
#include "base/ChatSession.h"

#include "gui/XmppAccountWindow.h"


XmppPlugin::XmppPlugin(QObject *parent) :
    QObject(parent)
{
}

Account *XmppPlugin::createAccount()
{
    return new XmppAccount();
}

QDialog *XmppPlugin::createAccountWindow(Account *account)
{
    return new XmppAccountWindow(this, dynamic_cast<XmppAccount*>(account));
}

void XmppPlugin::init(ApplicationController *app)
{
    this->m_app = app;
}

QXmppMessage::State &operator<<(QXmppMessage::State &xmppState, const ChatSession::State &state)
{
    switch(state) {
    case ChatSession::State::Composing:
        xmppState = QXmppMessage::State::Composing;
        break;
        
    case ChatSession::State::Paused:
        xmppState = QXmppMessage::State::Paused;
        break;
        
    case ChatSession::State::Gone:
        xmppState = QXmppMessage::State::Gone;
        break;
        
    case ChatSession::State::Unknown:
    default:
        xmppState = QXmppMessage::State::None;
        break;
    }
    
    return xmppState;
}

ChatSession::State &operator<<(ChatSession::State &state, const QXmppMessage::State &xmppState)
{
    switch(xmppState) {
    case QXmppMessage::State::Composing:
        state = ChatSession::State::Composing;
        break;
        
    case QXmppMessage::State::Paused:
        state = ChatSession::State::Paused;
        break;
        
    case QXmppMessage::State::Gone:
        state = ChatSession::State::Gone;
        break;
        
    case QXmppMessage::State::None:
    default:
        state = ChatSession::State::Unknown;
        break;
    }
    
    return state;
}

QXmppPresence &operator<<(QXmppPresence &presence, const Status &status)
{
    switch (status.type())
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
    case QXmppPresence::Available:
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
        
    case QXmppPresence::Unavailable:
    default:
        status.setType(Status::Offline);
        break;
    }
    
    return status;
}
