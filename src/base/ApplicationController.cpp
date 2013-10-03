#include "ApplicationController.h"

#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QSettings>

#include "plugins/protocols/xmpp/XmppAccount.h"
#include "plugins/protocols/xmpp/XmppContact.h"
#include "plugins/protocols/xmpp/gui/XmppAccountWindow.h"

#include "gui/GuiController.h"

ApplicationController::ApplicationController(QObject *parent) :
    QObject(parent)
{
    QCoreApplication::setOrganizationName("oxofrmbl");
    QCoreApplication::setApplicationName("oxofrmbl");
    
    discoverPlugins();

    //qDebug() << account->metaObject()->className();

    accountManager = new AccountManager(this);
    accountManager->load();
    
    auto gui = new GuiController(this);
    
    for(auto account : accountManager->getAccounts()) {
        account->connectToServer();
        
        connect(gui, &GuiController::quit, account, &Account::disconnectFromServer);
        connect(gui, &GuiController::quit, this, &ApplicationController::quit);
    
        contactList = new ContactList(account);
    
        connect(account, &Account::connected, contactList, &ContactList::retrieveContacts);
        
        gui->addContactList(contactList);
    }
}

ContactList *ApplicationController::getContactList()
{
    return contactList;
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
            
            protocolPlugins[protocol] = plugin;
        } else {
            qDebug() << loader.errorString();
        }
    }
}
