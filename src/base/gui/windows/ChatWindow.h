#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

#include "common.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(ChatSession *session, QWidget *parent = 0);
    ~ChatWindow();

signals:
    void messageSent(const ChatMessage *msg);

public slots:
    void updateContactStatus(Status *status);
    
    void messageReceived(const ChatMessage *msg);
    bool eventFilter(QObject *o, QEvent *e) override;

    void closeEvent(QCloseEvent *e) override;

protected:
    void sendMessage();

    ChatSession *session;
    Ui::ChatWindow *ui;

};

#endif // CHATWINDOW_H
