#include "ChatLogWidget.h"

#include <QDebug>

ChatLogWidget::ChatLogWidget(QWidget *parent) :
    QTextEdit(parent)
{
    clear();
}

void ChatLogWidget::addMessage(const ChatMessage *msg)
{
    QString sender = msg->isIncoming() ?
                QString("<b style='color: red'>%1</b>").arg(msg->getRemoteParticipant()->getDisplayName()) :
                QString("<b style='color: blue'>%1</b>").arg(msg->getLocalParticipant()->getDisplayName());

    QString message = msg->getBody();

    append(sender+": "+message);
}
