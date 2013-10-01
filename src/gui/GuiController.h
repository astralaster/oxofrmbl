#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "ApplicationController.h"
#include "base/ContactList.h"
#include "base/ChatSession.h"

#include "windows/ContactListWindow.h"
#include "windows/ChatWindow.h"
#include "windows/AccountsWindow.h"

class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(ApplicationController *app = 0);

signals:
    void quit();

public slots:
    void startChat(ChatSession *session);
    void activateChat(ChatSession *session);

    void showAccountsWindow();
    void activateContactList(QSystemTrayIcon::ActivationReason reason);

protected:
    QMenu *trayContextMenu() const;

    ApplicationController *app;

    QMap<ChatSession*, ChatWindow*> chatWindows;
    ContactListWindow *clw;
    AccountsWindow *aw = nullptr;

};

#endif // GUICONTROLLER_H
