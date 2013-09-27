#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QDebug>
#include <QKeyEvent>

ChatWindow::ChatWindow(Conversation *conversation, QWidget *parent) :
    QMainWindow(parent), conversation(conversation),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageEdit->installEventFilter(this);

    setWindowTitle(conversation->getContact()->getDisplayName());

    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    connect(this, &ChatWindow::messageSent, conversation, &Conversation::sendMessage);
    connect(conversation, &Conversation::messageReceived, this, &ChatWindow::messageReceived);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::messageReceived(const ChatMessage *msg)
{
    ui->messageLog->addItem(msg->getBody());
}

bool ChatWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->messageEdit && e->type() == QKeyEvent::KeyPress) {
        QKeyEvent *ev = (QKeyEvent*)e;

        if(ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return) {
            e->accept();
            ui->sendButton->click();

            return true;
        }
    }

    return false;
}

void ChatWindow::sendMessage()
{
    ChatMessage *msg = new ChatMessage(conversation->getContact(), false, ui->messageEdit->toPlainText());
    ui->messageLog->addItem(msg->getBody());

    ui->messageEdit->clear();
    ui->messageEdit->setFocus();

    emit messageSent(msg);
}
