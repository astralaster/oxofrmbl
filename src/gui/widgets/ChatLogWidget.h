#ifndef CHATLOGWIDGET_H
#define CHATLOGWIDGET_H

#include <QListWidget>
#include <QTextEdit>

#include "ChatMessage.h"

class ChatLogWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit ChatLogWidget(QWidget *parent = 0);

    void addMessage(const ChatMessage *msg);

signals:

public slots:

};

#endif // CHATLOGWIDGET_H