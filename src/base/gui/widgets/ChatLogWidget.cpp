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
    if(state == ChatSession::State::Gone) {
        append(QString("<b>%1 has left the building</b>").arg(m_contact->displayName()));
    }
    
    if(state == ChatSession::State::Composing) {
        m_stateLabel->setText("<b>...</b>");
        m_stateLabel->show();
    } else {
        m_stateLabel->hide();
    }
}

void ChatLogWidget::addMessage(ChatMessage *msg)
{
    QString time = msg->time().toString("hh:mm:ss");
    
    QString sender = msg->isIncoming() ?
        QString("<span style='color: red '>(%1) <b>%2</b></span>").arg(time).arg(msg->remoteParticipant()->displayName()) :
        QString("<span style='color: blue'>(%1) <b>%2</b></span>").arg(time).arg(msg->localParticipant()->displayName());

    QString message = msg->body();

    append(sender+": "+message);
}

void ChatLogWidget::resizeEvent(QResizeEvent *e)
{
    m_stateLabel->setGeometry(width()-25, height()-25, 25, 25);
    QTextEdit::resizeEvent(e);
}
