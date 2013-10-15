#include "ChatWindow.h"
#include "ui_ChatWindow.h"

#include <QKeyEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileDialog>

#include "gui/StatusIcon.h"
#include "base/Account.h"
#include "base/Contact.h"
#include "base/ChatSession.h"
#include "base/ChatMessage.h"
#include "base/Status.h"

ChatWindow::ChatWindow(ChatSession *session, QWidget *parent) :
    QWidget(parent, Qt::Window), m_typingTimeout(this), m_pausingTimeout(this), m_session(session),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->messageLog->setContact(session->contact());

    ui->messageLog->installEventFilter(this);
    ui->messageEdit->installEventFilter(this);

    setFocusProxy(ui->messageEdit);
    //ui->messageEdit->setFocus();
    
    ui->splitter->setSizes(QList<int>({0, 50}));
    
    auto contact = session->contact();

    setWindowTitle(contact->displayName());
    setWindowIcon(StatusIcon::forStatus(contact->status()));

    connect(this,    &ChatWindow::messageSent,  session, &ChatSession::sendMessage);
    connect(this,    &ChatWindow::stateChanged, session, &ChatSession::sendStateUpdate);

    connect(session, &ChatSession::messageReceived,  this, &ChatWindow::messageReceivedSlot);
    connect(session, &ChatSession::fileReceived, this, &ChatWindow::fileReceivedSlot);
    connect(session, &ChatSession::chatStateChanged, ui->messageLog, &ChatLogWidget::updateChatState);

    connect(contact, &Contact::statusChanged, this, &ChatWindow::updateContactStatus);
    
    connect(ui->messageEdit, &QTextEdit::textChanged, this, &ChatWindow::textChangedSlot);
    
    m_typingTimeout.setSingleShot(true);
    m_pausingTimeout.setSingleShot(true);

    m_newMessageBlink.setInterval(600);

    connect(&m_pausingTimeout, &QTimer::timeout, this, &ChatWindow::typingPausedSlot);

    connect(&m_newMessageBlink, SIGNAL(timeout()), this, SIGNAL(blink()));
    connect(this, &ChatWindow::blink, this, &ChatWindow::toggleIcon);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

ChatSession *ChatWindow::session()
{
    return m_session;
}

void ChatWindow::messageReceivedSlot(ChatMessage *msg)
{
    if(!hasFocus()) {
        m_newMessageBlink.start();
    }
    
    ui->messageLog->addMessage(msg);
}

void ChatWindow::fileReceivedSlot(FileTransfer *transfer)
{
    auto dialog = new QFileDialog(this, "Select directory to save file");

    dialog->setOption(QFileDialog::ShowDirsOnly);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setAcceptMode(QFileDialog::AcceptOpen);

    dialog->setLabelText(QFileDialog::Accept, "Select");

    if(dialog->exec() == QFileDialog::Accepted)
    {
        auto dir = dialog->directory();
        auto fileName = dir.filePath(transfer->fileName());

        if(dir.exists())
        {
            transfer->accept(fileName);
            return;
        }
    }

    transfer->refuse();
}

void ChatWindow::updateContactStatus(Status *status)
{
    setWindowIcon(StatusIcon::forStatus(status));
    emit iconChanged(windowIcon());
}

void ChatWindow::typingPausedSlot()
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

void ChatWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
    e->acceptProposedAction();
}

void ChatWindow::dropEvent(QDropEvent *e)
{
    auto mime = e->mimeData();

    if(mime->hasUrls())
    {
        for(QUrl url: mime->urls())
        {
            if(url.isLocalFile())
            {
                auto fileTransfer = new FileTransfer(m_session, false, url.toLocalFile());
                m_session->account()->sendFile(fileTransfer);
            }
        }

        e->accept();
    }
}

void ChatWindow::showEvent(QShowEvent *e)
{
    //activateWindow();
    ui->messageEdit->setFocus();
    
    QWidget::showEvent(e);
}

void ChatWindow::focusInEvent(QFocusEvent *e)
{
    if(m_newMessageBlink.isActive())
    {
        m_newMessageBlink.stop();
        emit blink(true);
    }

    ui->messageEdit->setFocus();

    QWidget::focusInEvent(e);
}

void ChatWindow::closeEvent(QCloseEvent *e)
{
    m_newMessageBlink.stop();
    m_pausingTimeout.stop();
    m_typingTimeout.stop();
    
    emit stateChanged(ChatSession::State::Gone);
    m_session->account()->endSession(m_session);
    
    e->accept();
    QWidget::closeEvent(e);
}

void ChatWindow::setWindowIcon(const QIcon &icon)
{
    emit iconChanged(icon);
    QWidget::setWindowIcon(icon);
}

void ChatWindow::setWindowTitle(const QString &title)
{
    emit titleChanged(title);
    QWidget::setWindowTitle(title);
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
