#include "TabbedChatWindow.h"
#include "ui_TabbedChatWindow.h"

#include <QKeyEvent>

#include "../GuiController.h"

TabbedChatWindow::TabbedChatWindow(GuiController *gui, QWidget *parent) :
    QMainWindow(parent), m_gui(gui),
    ui(new Ui::TabbedChatWindow)
{
    ui->setupUi(this);
    
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &TabbedChatWindow::closeTab);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &TabbedChatWindow::switchTab);
}

TabbedChatWindow::~TabbedChatWindow()
{
    delete ui;
}

int TabbedChatWindow::addTab(ChatWindow *window)
{
    ui->tabWidget->addTab(window, window->windowIcon(), window->windowTitle());
    
    connect(window, &ChatWindow::iconChanged, this, &TabbedChatWindow::updateTabIcon);
    connect(window->session(), &ChatSession::chatStateChanged, this, &TabbedChatWindow::updateTabState);
    //connect(window, &ChatWindow::titleChanged, this, &TabbedChatWindow::updateTabTitle);
    
    int index = ui->tabWidget->indexOf(window);
    
    ui->tabWidget->setCurrentIndex(index);
    showNormal();
    activateWindow();
    
    return index;
}

void TabbedChatWindow::activateChatWindow(ChatWindow *window)
{
    activateTab(ui->tabWidget->indexOf(window));
}

void TabbedChatWindow::updateTabIcon(const QIcon &icon)
{
    auto sender = qobject_cast<ChatWindow*>(QObject::sender());
    auto index = ui->tabWidget->indexOf(sender);
    
    if(ui->tabWidget->currentIndex() == index) {
        setWindowIcon(icon);
    }
    
    ui->tabWidget->setTabIcon(index, icon);
}

void TabbedChatWindow::updateTabTitle(const QString &title)
{
    auto sender = qobject_cast<ChatWindow*>(QObject::sender());
    auto index = ui->tabWidget->indexOf(sender);
    
    if(ui->tabWidget->currentIndex() == index) {
        setWindowTitle(title);
    }
    
    ui->tabWidget->setTabText(index, title);
}

void TabbedChatWindow::updateTabState(ChatSession::State state)
{
    auto sender = qobject_cast<ChatSession*>(QObject::sender());
    auto index = ui->tabWidget->indexOf(m_gui->chatWindowForSession(sender));
    auto tabBar = ui->tabWidget->tabBar();
    
    switch (state) {
    case ChatSession::State::Composing:
        tabBar->setTabTextColor(index, QColor("red"));
        break;

    case ChatSession::State::Gone:
        tabBar->setTabTextColor(index, QColor("#ccc"));
        break;

    default:
        tabBar->setTabTextColor(index, QColor("#333"));
        break;
    }
}

void TabbedChatWindow::activateTab(int tabIndex)
{
    ui->tabWidget->setCurrentIndex(tabIndex);
    activateWindow();
}

void TabbedChatWindow::closeTab(int tabIndex)
{
    if(tabIndex >= 0)
    {
        ui->tabWidget->widget(tabIndex)->close();
        ui->tabWidget->removeTab(tabIndex);
        
        if(ui->tabWidget->count() == 0) {
            close();
        }
    }
}

void TabbedChatWindow::switchTab(int tabIndex)
{
    if(tabIndex >= 0) {
        auto window = ui->tabWidget->widget(tabIndex);
        setWindowTitle(window->windowTitle());
        setWindowIcon(window->windowIcon());
    }
}

void TabbedChatWindow::mousePressEvent(QMouseEvent *e)
{
    emit ui->tabWidget->tabCloseRequested(ui->tabWidget->tabBar()->tabAt(e->pos()));
}

void TabbedChatWindow::closeEvent(QCloseEvent *e)
{
    while(ui->tabWidget->count() > 0) {
        ui->tabWidget->widget(0)->close();
        ui->tabWidget->removeTab(0);
    }
}
