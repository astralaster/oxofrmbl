#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>

#include "ContactList.h"
#include "Chat.h"
#include "ContactListWindow.h"
#include "ChatWindow.h"

class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(ContactList *cl, QObject *parent = 0);

signals:
    void exitApp();

public slots:
    void startChat(Chat *chat);
    void activateChat(Chat *chat);

protected:
    QMap<Chat*, ChatWindow*> chatWindows;
    ContactListWindow clw;

};

#endif // GUICONTROLLER_H
