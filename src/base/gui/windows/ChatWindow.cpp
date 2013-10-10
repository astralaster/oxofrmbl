#include "ChatWindow.h"
#include "ui_ChatWindow.h"


#include <QKeyEvent>

#include "gui/StatusIcon.h"
#include "base/Account.h"
#include "base/Contact.h"
#include "base/ChatSession.h"
#include "base/ChatMessage.h"
#include "base/Status.h"

ChatWindow::ChatWindow(ChatSession *session, QWidget *parent) :
    QMainWindow(parent), m_session(session), m_typingTimeout(this),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageLog->setContact(session->contact());

    ui->messageLog->installEventFilter(this);
    ui->messageEdit->installEventFilter(this);
    ui->messageEdit->setFocus();
    
    ui->splitter->setSizes(QList<int>({0, 50}));
    
    auto contact = session->contact();

    setWindowTitle(contact->displayName());
    setWindowIcon(StatusIcon::forStatus(contact->status()));

    connect(this, &ChatWindow::messageSent, session, &ChatSession::sendMessage);
    connect(this, &ChatWindow::stateChanged, session, &ChatSession::sendStateUpdate);
    connect(session, &ChatSession::messageReceived, ui->messageLog, &ChatLogWidget:: addMessage);
    connect(session, &ChatSession::chatStateChanged, ui->messageLog, &ChatLogWidget::updateChatState);

    connect(contact, &Contact::statusChanged, this, &ChatWindow::updateContactStatus);

    connect(&m_typingTimeout, &QTimer::timeout, this, &ChatWindow::typingPaused);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::updateContactStatus(Status *status)
{
    setWindowIcon(StatusIcon::forStatus(status));
    emit iconChanged(windowIcon());
}

void ChatWindow::typingPaused()
{
    emit stateChanged(ChatSession::State::Paused);
}

bool ChatWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->messageEdit && e->type() == QKeyEvent::KeyPress)
    {
        QKeyEvent *ev = (QKeyEvent*)e;

        if((ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return))
        {
            if(!(ev->modifiers() & Qt::SHIFT))
            {
                e->accept();
                sendMessage();
                return true;
            }
        }
    }
    else if(o == ui->messageLog && e->type() == QKeyEvent::KeyPress)
    {
        QKeyEvent *ev = (QKeyEvent*)e;

        e->accept();
        ui->messageEdit->setFocus();
    }
    else
    {
        e->ignore();
        emit stateChanged(ChatSession::State::Composing);
        m_typingTimeout.start(5000);
    }

    return false;
}

void ChatWindow::showEvent(QShowEvent *e)
{
    activateWindow();
    ui->messageEdit->setFocus();
}

void ChatWindow::closeEvent(QCloseEvent *e)
{
    m_session->account()->endSession(m_session);
    e->accept();
}

void ChatWindow::sendMessage()
{
    QString body = ui->messageEdit->toPlainText();

    if(!body.isEmpty()) {
        auto msg = new ChatMessage(m_session, false, body);
        ui->messageLog->addMessage(msg);

        ui->messageEdit->clear();
        ui->messageEdit->setFocus();

        emit messageSent(msg);
    }
}
