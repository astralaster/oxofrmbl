#include "ChatLogWidget.h"

#include "base/Account.h"
#include "base/Contact.h"
#include "base/ChatMessage.h"

ChatLogWidget::ChatLogWidget(QWidget *parent) :
    QTextEdit(parent)
{
    clear();
    m_stateLabel = new QLabel(this);
}

void ChatLogWidget::setContact(Contact *contact)
{
    m_contact = contact;
}

void ChatLogWidget::updateChatState(ChatSession::State state)
{
    /*QString text  = QString("<b>%1 %2</b>").arg(m_contact->displayName());

    switch (state) {
    case ChatSession::State::Composing:
        text = text.arg("is typing");
        break;

    case ChatSession::State::Paused:
        text = text.arg("has stopped typing");
        break;

    case ChatSession::State::Gone:
        text = text.arg("has left the building");
        break;

    default:
        text = "";
        break;
    }

    m_stateLabel->setText(text);
    m_stateLabel->setGeometry(5, height()-25, width(), 25);
    m_stateLabel->show();*/
}

void ChatLogWidget::addMessage(const ChatMessage *msg)
{
    QString time = msg->time().toString("hh:mm:ss");
    
    QString sender = msg->isIncoming() ?
        QString("<span style='color: red '>(%1) <b>%2</b></span>").arg(time).arg(msg->remoteParticipant()->displayName()) :
        QString("<span style='color: blue'>(%1) <b>%2</b></span>").arg(time).arg(msg->localParticipant()->displayName());

    QString message = msg->body();

    append(sender+": "+message);
}
