#ifndef TABBEDCHATWINDOW_H
#define TABBEDCHATWINDOW_H

#include <QMainWindow>

#include "ChatWindow.h"

namespace Ui {
class TabbedChatWindow;
}

class TabbedChatWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TabbedChatWindow(QWidget *parent = 0);
    ~TabbedChatWindow();
    
    
public slots:
    void activateChatWindow(ChatWindow *window);
    void updateTabIcon(const QIcon &icon);
    
    int addTab(ChatWindow *window);
    void activateTab(int tabIndex);
    void closeTab(int tabIndex);
    void switchTab(int tabIndex);
    
    void mousePressEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    
private:
    Ui::TabbedChatWindow *ui;
};

#endif // TABBEDCHATWINDOW_H
