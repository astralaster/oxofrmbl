#ifndef CHATLOGWIDGET_H
#define CHATLOGWIDGET_H

#include <QListWidget>
#include <QTextEdit>

#include "base/ChatMessage.h"

class ChatLogWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit ChatLogWidget(QWidget *parent = 0);

signals:

public slots:
    void addMessage(const ChatMessage *msg);

};

#endif // CHATLOGWIDGET_H
