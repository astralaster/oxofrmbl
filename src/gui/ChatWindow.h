#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

#include "Contact.h"
#include "Conversation.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(Conversation *conversation, QWidget *parent = 0);
    ~ChatWindow();

signals:
    void messageSent(const ChatMessage *msg);

public slots:
    void messageReceived(const ChatMessage *msg);
    bool eventFilter(QObject *o, QEvent *e) override;

protected:
    void sendMessage();

    Conversation *conversation;
    Ui::ChatWindow *ui;

};

#endif // CHATWINDOW_H
