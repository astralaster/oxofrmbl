#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>

#include "base/ContactList.h"
#include "base/AccountManager.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = 0);

    ContactList *getContactList();
    AccountManager *getAccountManager();

signals:
    void quit();

protected:
    ContactList *contactList;
    AccountManager *accountManager;

};

#endif // APPLICATIONCONTROLLER_H
