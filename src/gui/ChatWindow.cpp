#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QDebug>
#include <QKeyEvent>

ChatWindow::ChatWindow(Chat *chat, QWidget *parent) :
    QMainWindow(parent), chat(chat),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageEdit->installEventFilter(this);
    ui->messageEdit->setFocus();

    setWindowTitle(chat->getContact()->getDisplayName());

    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    connect(this, &ChatWindow::messageSent, chat, &Chat::sendMessage);
    connect(chat, &Chat::messageReceived, this, &ChatWindow::messageReceived);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::messageReceived(const ChatMessage *msg)
{
    ui->messageLog->addMessage(msg);
}

bool ChatWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->messageEdit && e->type() == QKeyEvent::KeyPress) {
        QKeyEvent *ev = (QKeyEvent*)e;

        if((ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return)) {

            if(!(ev->modifiers() & Qt::SHIFT)) {
                e->accept();
                sendMessage();
            }

            return true;
        }
    }

    return false;
}

void ChatWindow::closeEvent(QCloseEvent *e)
{
    chat->getAccount()->endChat(chat);
}

void ChatWindow::sendMessage()
{
    QString body = ui->messageEdit->toPlainText();

    if(!body.isEmpty()) {
        auto msg = new ChatMessage(chat, false, body);
        ui->messageLog->addMessage(msg);

        ui->messageEdit->clear();
        ui->messageEdit->setFocus();

        emit messageSent(msg);
    }
}
