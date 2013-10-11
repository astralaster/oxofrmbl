#ifndef TABBEDCHATWINDOW_H
#define TABBEDCHATWINDOW_H

#include <QMainWindow>

#include "ChatWindow.h"

class GuiController;

namespace Ui {
class TabbedChatWindow;
}

class TabbedChatWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TabbedChatWindow(GuiController *gui, QWidget *parent = nullptr);
    ~TabbedChatWindow();
    
public slots:
    void activateChatWindow(ChatWindow *window);
    void updateTabIcon(const QIcon &icon);
    void updateTabTitle(const QString &title);
    void updateTabState(ChatSession::State state);
    
    int addTab(ChatWindow *window);
    void activateTab(int tabIndex);
    void closeTab(int tabIndex);
    void switchTab(int tabIndex);
    
    void mousePressEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    
private:
    GuiController *m_gui;
    Ui::TabbedChatWindow *ui;
};

#endif // TABBEDCHATWINDOW_H
