#include "GuiController.h"

#include <QApplication>

GuiController::GuiController(ContactList *cl, QObject *parent) :
    QObject(parent)
{
    connect(cl->getAccount(), &Account::chatStarted, this, &GuiController::startChat);
    connect(cl->getAccount(), &Account::chatActivated, this, &GuiController::activateChat);

    connect(&clw, &ContactListWindow::windowClosed, cl->getAccount(), &Account::disconnectFromServer);
    connect(&clw, &ContactListWindow::windowClosed, QApplication::exit);

    clw.getList()->setModel(cl);
    clw.show();
}

void GuiController::startChat(Chat *chat)
{
    auto cw = new ChatWindow(chat);
    chatWindows[chat] = cw;

    cw->show();
}

void GuiController::activateChat(Chat *chat)
{
    ChatWindow *cw = chatWindows[chat];

    cw->showNormal();
    cw->activateWindow();
}
