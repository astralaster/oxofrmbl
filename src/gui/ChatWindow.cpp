#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QDebug>
#include <QKeyEvent>

ChatWindow::ChatWindow(Contact *contact, QWidget *parent) :
    QMainWindow(parent), contact(contact),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageEdit->installEventFilter(this);

    setWindowTitle(contact->getDisplayName());

    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    connect(this, &ChatWindow::messageSent, contact->getAccount(), &Account::sendMessage);
    connect(contact->getAccount(), &Account::messageReceived, this, &ChatWindow::messageReceived);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::messageReceived(const QString &msg)
{
    ui->messageLog->addItem(msg);
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
    ChatMessage *msg = new ChatMessage(contact, ui->messageEdit->toPlainText());
    ui->messageLog->addItem(msg->getBody());

    ui->messageEdit->clear();
    ui->messageEdit->setFocus();

    emit messageSent(msg);
}
