#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QKeyEvent>
#include <QDebug>

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
    connect(session, &ChatSession::messageReceived,  this, &ChatWindow::receiveMessage);
    connect(session, &ChatSession::chatStateChanged, ui->messageLog, &ChatLogWidget::updateChatState);

    connect(contact, &Contact::statusChanged, this, &ChatWindow::updateContactStatus);
    
    connect(ui->messageEdit, &QTextEdit::textChanged, this, &ChatWindow::textChangedSlot);
    
    m_typingTimeout.setSingleShot(true);
    m_pausingTimeout.setSingleShot(true);

    connect(&m_pausingTimeout, &QTimer::timeout, this, &ChatWindow::typingPaused);
    connect(&m_newMessageBlink, SIGNAL(timeout()), this, SLOT(toggleIcon()));
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

ChatSession *ChatWindow::session()
{
    return m_session;
}

void ChatWindow::receiveMessage(ChatMessage *msg)
{
    if(!isActiveWindow()) {
        m_newMessageBlink.start(1000);
    }
    
    ui->messageLog->addMessage(msg);
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

void ChatWindow::toggleIcon(bool forceStatus)
{
    QIcon statusIcon = StatusIcon::forStatus(m_session->contact()->status());
    
    if(forceStatus || windowIcon().name() != statusIcon.name()) {
        setWindowIcon(statusIcon);
    } else {
        setWindowIcon(QIcon::fromTheme("mail-message-new"));
    }
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
        }
        else if(o == ui->messageLog)
        {
            e->accept();
            ui->messageEdit->setFocus();
        }
    }
    else if(e->type() == QFocusEvent::FocusIn)
    {
        focusInEvent((QFocusEvent*)e);
    }
    
    return false;
}

void ChatWindow::showEvent(QShowEvent *e)
{
    activateWindow();
    ui->messageEdit->setFocus();
    
    QMainWindow::showEvent(e);
}

void ChatWindow::focusInEvent(QFocusEvent *e)
{
    m_newMessageBlink.stop();
    toggleIcon(true);
    QMainWindow::focusInEvent(e);
}

void ChatWindow::closeEvent(QCloseEvent *e)
{
    m_newMessageBlink.stop();
    m_pausingTimeout.stop();
    m_typingTimeout.stop();
    
    emit stateChanged(ChatSession::State::Gone);
    m_session->account()->endSession(m_session);
    
    e->accept();
    QMainWindow::closeEvent(e);
}

void ChatWindow::setWindowIcon(const QIcon &icon)
{
    emit iconChanged(icon);
    QMainWindow::setWindowIcon(icon);
}

void ChatWindow::setWindowTitle(const QString &title)
{
    emit titleChanged(title);
    QMainWindow::setWindowTitle(title);
}

void ChatWindow::textChangedSlot()
{
    if(ui->messageEdit->document()->isEmpty())
    {
        emit stateChanged(ChatSession::State::Unknown);
        
        m_typingTimeout.stop();
        m_pausingTimeout.stop();
    }
    else
    {
        if(!m_pausingTimeout.isActive())
        {
            emit stateChanged(ChatSession::State::Composing);
        }
        
        m_typingTimeout.start(1000);
        m_pausingTimeout.start(5000);
    }
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
