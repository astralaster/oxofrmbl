#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QDebug>
#include <QKeyEvent>

ChatWindow::ChatWindow(ChatSession *session, QWidget *parent) :
    QMainWindow(parent), session(session),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageEdit->installEventFilter(this);
    ui->messageEdit->setFocus();

    ui->sendButton->setVisible(false);

    setWindowTitle(session->getContact()->getDisplayName());

    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    connect(this, &ChatWindow::messageSent, session, &ChatSession::sendMessage);
    connect(session, &ChatSession::messageReceived, this, &ChatWindow::messageReceived);
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
                return true;
            }
        }
    }

    return false;
}

void ChatWindow::closeEvent(QCloseEvent *e)
{
    session->getAccount()->endSession(session);
    e->accept();
}

void ChatWindow::sendMessage()
{
    QString body = ui->messageEdit->toPlainText();

    if(!body.isEmpty()) {
        auto msg = new ChatMessage(session, false, body);
        ui->messageLog->addMessage(msg);

        ui->messageEdit->clear();
        ui->messageEdit->setFocus();

        emit messageSent(msg);
    }
}