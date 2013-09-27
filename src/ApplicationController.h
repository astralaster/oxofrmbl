#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>

#include "ContactList.h"
#include "AccountManager.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = 0);

signals:

public slots:

protected:
    //ContactList contactList;
    AccountManager accountManager;

};

#endif // APPLICATIONCONTROLLER_H
