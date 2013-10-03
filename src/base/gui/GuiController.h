#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "../ApplicationController.h"
#include "ContactList.h"
#include "base/ChatSession.h"

#include "windows/ContactListWindow.h"
#include "windows/ChatWindow.h"
#include "windows/AccountsWindow.h"

class ContactListWindow;

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
    void activateContactList(QSystemTrayIcon::ActivationReason reason);
    
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
