#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>

#include "interfaces/ProtocolPluginInterface.h"

#include "common.h"
#include "base/ContactList.h"
#include "base/AccountManager.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = 0);

    ContactList *getContactList();
    AccountManager *getAccountManager();
    
    QList<QString> getProtocolPluginNames() const;
    ProtocolPlugin *getProtocolPlugin(const QString &protocol);

signals:
    void quit();
    
public slots:
    void discoverPlugins();

protected:
    QMap<QString, ProtocolPlugin*> protocolPlugins;
    
    ContactList *contactList;
    AccountManager *accountManager;

};

#endif // APPLICATIONCONTROLLER_H
