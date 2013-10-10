#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "common.h"

#include "base/ChatSession.h"
#include "base/Status.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(ChatSession *session, QWidget *parent = nullptr);
    ~ChatWindow();

signals:
    void messageSent(const ChatMessage *msg);
    void stateChanged(ChatSession::State state);
    void iconChanged(const QIcon &icon);

public slots:
    void updateContactStatus(Status *status);

    void typingPaused();
    
    //void messageReceived(const ChatMessage *msg);
    bool eventFilter(QObject *o, QEvent *e) override;

    void showEvent(QShowEvent *e) override;
    void closeEvent(QCloseEvent *e) override;

protected:
    void sendMessage();

    QTimer m_typingTimeout;

    ChatSession *m_session;
    Ui::ChatWindow *ui;

};

#endif // CHATWINDOW_H
