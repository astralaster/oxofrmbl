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

    m_accountManager = new AccountManager(this);
    m_gui = new GuiController(this);
    
    connect(m_accountManager, &AccountManager::accountAdded,   m_gui, &GuiController::addAccount);
    connect(m_accountManager, &AccountManager::accountRemoved, m_gui, &GuiController::removeAccount);
    
    m_accountManager->load();
    
    m_accountManager->connectAccounts();
    
    m_gui->show();
}

AccountManager *ApplicationController::accountManager()
{
    return m_accountManager;
}

QList<QString> ApplicationController::protocolPluginNames() const
{
    return protocolPlugins.keys();
}

ProtocolPlugin *ApplicationController::protocolPlugin(const QString &protocol)
{
    return protocolPlugins[protocol];
}

void ApplicationController::discoverPlugins()
{
    QDir path(OXOFRMBL_LIBDIR);
    path.cd("plugins/protocols");
    
    for(auto protocol : path.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        path.cd(protocol);
        
        qDebug() << "entering " << path.path();
        
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
