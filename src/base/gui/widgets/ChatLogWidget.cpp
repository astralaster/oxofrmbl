#include "ChatLogWidget.h"

#include "base/Account.h"
#include "base/Contact.h"
#include "base/ChatMessage.h"

ChatLogWidget::ChatLogWidget(QWidget *parent) :
    QTextEdit(parent)
{
    clear();
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
