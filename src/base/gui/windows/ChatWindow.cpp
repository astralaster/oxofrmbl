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
    QMainWindow(parent), m_typingTimeout(this), m_pausingTimeout(this), m_session(session),
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

    connect(this,    &ChatWindow::messageSent,  session, &ChatSession::sendMessage);
    connect(this,    &ChatWindow::stateChanged, session, &ChatSession::sendStateUpdate);
    connect(session, &ChatSession::messageReceived,  ui->messageLog, &ChatLogWidget::addMessage);
    connect(session, &ChatSession::chatStateChanged, ui->messageLog, &ChatLogWidget::updateChatState);

    connect(contact, &Contact::statusChanged, this, &ChatWindow::updateContactStatus);
    
    m_typingTimeout.setSingleShot(true);
    m_pausingTimeout.setSingleShot(true);

    connect(&m_pausingTimeout, &QTimer::timeout, this, &ChatWindow::typingPaused);
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
    if(e->type() == QKeyEvent::KeyPress)
    {
        if(o == ui->messageEdit)
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
            else
            {
                e->ignore();
                
                if(!m_pausingTimeout.isActive()) {
                    emit stateChanged(ChatSession::State::Composing);
                }
                
                m_typingTimeout.start(1000);
                m_pausingTimeout.start(5000);
            }
        }
        else if(o == ui->messageLog)
        {
            e->accept();
            ui->messageEdit->setFocus();
        }
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
    emit stateChanged(ChatSession::State::Gone);
    m_session->account()->endSession(m_session);
    e->accept();
}

void ChatWindow::sendMessage()
{
    m_typingTimeout.stop();
    m_pausingTimeout.stop();
    
    QString body = ui->messageEdit->toPlainText();

    if(!body.isEmpty()) {
        auto msg = new ChatMessage(m_session, false, body);
        ui->messageLog->addMessage(msg);

        ui->messageEdit->clear();
        ui->messageEdit->setFocus();

        emit messageSent(msg);
    }
}
