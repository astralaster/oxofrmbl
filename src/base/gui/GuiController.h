#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "common.h"
#include "base/ApplicationController.h"

#include "AccountList.h"
#include "ContactList.h"
#include "windows/AccountsWindow.h"
#include "windows/ChatWindow.h"
#include "windows/TabbedChatWindow.h"
#include "windows/ContactListWindow.h"

class ApplicationController;
class ContactListWindow;
class AccountsWindow;
class AccountList;

class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(ApplicationController *m_app = 0);
    
    ChatWindow *chatWindowForSession(ChatSession *session);
    AccountList *accountList();

signals:
    void terminated();

public slots:
    void show();
    void quit();
    void startSession(ChatSession *session);
    void activateSession(ChatSession *session);
    void updateStatus(Status *status);
    void updateStatusIcon(const QIcon &icon);
    void toggleStatusIcon(bool forceStatus);

public slots:
    void showAccountsWindow();
    void showAboutDialog();
    void showAddContactDialog();
    void trayMenuTriggered(QSystemTrayIcon::ActivationReason reason);
    
public slots:
    void confirmContact(Contact *Contact);
    void addAccount(Account *account);
    void removeAccount(Account *account);
    
private:
    QMenu *trayContextMenu() const;

private:
    QSystemTrayIcon *m_trayIcon;

    AccountList *m_accountList;

    ApplicationController *m_app = nullptr;
    ContactListWindow *m_contactListWindow = nullptr;
    AccountsWindow *m_accountsWindow = nullptr;
    
    QMap<Account*, ContactList*> m_contactLists;
    QMap<ChatSession*, ChatWindow*> m_chatWindows;
    TabbedChatWindow *m_tabbedChatWindow;

    bool m_useTabs = true;
    Status *m_status;

};

#endif // GUICONTROLLER_H
