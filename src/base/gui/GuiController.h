#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "common.h"
#include "base/ApplicationController.h"

#include "ContactList.h"
#include "windows/AccountsWindow.h"
#include "windows/ChatWindow.h"
#include "windows/ContactListWindow.h"

class ApplicationController;
class ContactListWindow;
class AccountsWindow;

class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(ApplicationController *m_app = 0);

signals:
    void quit();

public slots:
    void show();
    void startChat(ChatSession *session);
    void activateChat(ChatSession *session);
    void closeTab(int tabIndex);
    void changeStatusIcon(Status *status);

    void showAccountsWindow();
    void showAboutDialog();
    void showAddContactDialog();
    void trayMenuTriggered(QSystemTrayIcon::ActivationReason reason);
    
    void handleError();
    
public slots:
    void addAccount(Account *account);
    void removeAccount(Account *account);
    
private:
    QMenu *trayContextMenu() const;

private:
    QSystemTrayIcon *m_trayIcon;

    ApplicationController *m_app = nullptr;
    ContactListWindow *m_contactListWindow = nullptr;
    AccountsWindow *m_accountsWindow = nullptr;
    
    QMap<Account*, ContactList*> m_contactLists;
    QMap<ChatSession*, ChatWindow*> m_chatWindows;

    QTabWidget *m_tabMain = nullptr;

    bool tabbing = true;

};

#endif // GUICONTROLLER_H
