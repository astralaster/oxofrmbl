#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QDebug>
#include <QKeyEvent>

#include "gui/StatusIcon.h"
#include "base/Account.h"
#include "base/Contact.h"
#include "base/ChatSession.h"
#include "base/ChatMessage.h"
#include "base/Status.h"

ChatWindow::ChatWindow(ChatSession *session, QWidget *parent) :
    QMainWindow(parent), session(session),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageEdit->installEventFilter(this);
    ui->messageEdit->setFocus();

    ui->sendButton->setVisible(false);
    
    auto contact = session->contact();

    setWindowTitle(contact->displayName());
    setWindowIcon(StatusIcon::forStatus(contact->status()));

    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    connect(this, &ChatWindow::messageSent, session, &ChatSession::sendMessage);
    connect(session, &ChatSession::messageReceived, this, &ChatWindow::messageReceived);
    connect(contact, &Contact::statusChanged, this, &ChatWindow::updateContactStatus);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::updateContactStatus(Status *status)
{
    setWindowIcon(StatusIcon::forStatus(status));
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
    session->account()->endSession(session);
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
