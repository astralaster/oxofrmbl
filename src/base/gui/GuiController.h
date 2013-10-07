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
    explicit GuiController(ApplicationController *app = 0);

signals:
    void quit();

public slots:
    void show();
    void startChat(ChatSession *session);
    void activateChat(ChatSession *session);

    void showAccountsWindow();
    void showAboutDialog();
    void showAddContactDialog();
    void trayMenuTriggered(QSystemTrayIcon::ActivationReason reason);
    
    void handleError();
    
public slots:
    void addAccount(Account *account);
    void removeAccount(Account *account);

protected:
    QMenu *trayContextMenu() const;

    ApplicationController *app = nullptr;
    ContactListWindow *clw = nullptr;
    AccountsWindow *aw = nullptr;
    
    QMap<Account*, ContactList*> contactLists;
    QMap<ChatSession*, ChatWindow*> chatWindows;

};

#endif // GUICONTROLLER_H
