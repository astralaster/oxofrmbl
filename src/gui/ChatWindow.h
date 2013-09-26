#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

#include "Contact.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(Contact *contact, QWidget *parent = 0);
    ~ChatWindow();

signals:
    void messageSent(const ChatMessage *msg);

public slots:
    void messageReceived(const QString &msg);
    bool eventFilter(QObject *o, QEvent *e) override;

protected:
    void sendMessage();

    Contact *contact;
    Ui::ChatWindow *ui;

};

#endif // CHATWINDOW_H
