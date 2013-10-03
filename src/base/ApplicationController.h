#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>

#include "interfaces/ProtocolPluginInterface.h"

#include "common.h"
#include "base/AccountManager.h"

#include "gui/GuiController.h"


class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = 0);

    AccountManager *getAccountManager();
    
    QList<QString> getProtocolPluginNames() const;
    ProtocolPlugin *getProtocolPlugin(const QString &protocol);

signals:
    void quit();
    
public slots:
    void addAccount(Account *account);
    void discoverPlugins();

protected:
    QMap<QString, ProtocolPlugin*> protocolPlugins;
    
    GuiController *gui = nullptr;
    AccountManager *accountManager = nullptr;

};

#endif // APPLICATIONCONTROLLER_H
