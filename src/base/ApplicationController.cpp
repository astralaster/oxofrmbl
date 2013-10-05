#include "ApplicationController.h"

#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include <QSettings>

#include "AccountManager.h"
#include "Account.h"
#include "gui/GuiController.h"
#include "interfaces/ProtocolPluginInterface.h"

ApplicationController::ApplicationController(QObject *parent) :
    QObject(parent)
{
    QCoreApplication::setOrganizationName("oxofrmbl");
    QCoreApplication::setApplicationName("oxofrmbl");
    
    discoverPlugins();

    //qDebug() << account->metaObject()->className();

    accountManager = new AccountManager(this);    
    gui = new GuiController(this);
    
    connect(accountManager, &AccountManager::accountAdded,   gui, &GuiController::addAccount);
    connect(accountManager, &AccountManager::accountRemoved, gui, &GuiController::removeAccount);
    
    accountManager->load();
    
    accountManager->connectAccounts();
    
    gui->show();
}

AccountManager *ApplicationController::getAccountManager()
{
    return accountManager;
}

QList<QString> ApplicationController::getProtocolPluginNames() const
{
    return protocolPlugins.keys();
}

ProtocolPlugin *ApplicationController::getProtocolPlugin(const QString &protocol)
{
    return protocolPlugins[protocol];
}

void ApplicationController::addAccount(Account *account)
{
    gui->addAccount(account);
    
    /*if(account->isConnected()) {
        
    }*/
}

void ApplicationController::discoverPlugins()
{
    QDir path(QApplication::applicationDirPath());
    path.cd("plugins/protocols/");
    
    for(auto protocol : path.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        path.cd(protocol);
        
        QPluginLoader loader(path.absoluteFilePath(QString("lib%1_plugin.so").arg(protocol)));
        loader.load();
        
        if(loader.isLoaded()) {
            ProtocolPlugin *plugin = qobject_cast<ProtocolPlugin*>(loader.instance());
            plugin->init(this);
            
            qDebug() << QString("loaded %1 plugin").arg(protocol);
            
            protocolPlugins[protocol] = plugin;
        } else {
            qDebug() << loader.errorString();
        }
    }
}
