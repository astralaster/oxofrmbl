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
    
    ChatSession *session();

signals:
    void messageSent(const ChatMessage *msg);
    void stateChanged(ChatSession::State state);
    void iconChanged(const QIcon &icon);
    void titleChanged(const QString &title);

public slots:
    void receiveMessage(const ChatMessage *msg);
    void updateContactStatus(Status *status);
    void typingPaused();
    
    void toggleIcon(bool forceStatus = false);
    
    //void messageReceived(const ChatMessage *msg);
    bool eventFilter(QObject *o, QEvent *e) override;

    void showEvent(QShowEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    
    void setWindowIcon(const QIcon &icon);
    void setWindowTitle(const QString &title);
    
private slots:
    void textChangedSlot();

private:
    void sendMessage();
    
    QTimer m_newMessageBlink;

    QTimer m_typingTimeout;
    QTimer m_pausingTimeout;

    ChatSession *m_session;
    Ui::ChatWindow *ui;

};

#endif // CHATWINDOW_H
