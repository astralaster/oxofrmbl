#include "AccountManager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QSettings>

#include "Account.h"
#include "ApplicationController.h"
#include "interfaces/ProtocolPluginInterface.h"

AccountManager::AccountManager(ApplicationController *app, QObject *parent) : QAbstractListModel(parent), m_app(app)
{
    connect(this, &AccountManager::changed, this, &AccountManager::dataChangedSlot);
}

Account *AccountManager::account(int index)
{
    return m_accounts[index];
}

void AccountManager::addAccount(Account *account, bool saveData)
{
    m_accounts << account;
    connect(account, &Account::accountSaved, this, &AccountManager::save);
    
    emit accountAdded(account);
    emit changed(saveData);
}

void AccountManager::removeAccount(Account *account)
{
    emit accountRemoved(account);
    
    m_accounts.removeOne(account);
    account->remove();
    
    delete account;
    
    emit changed(true);
}

QList<Account *> AccountManager::accounts() const
{
    return m_accounts;
}

int AccountManager::rowCount(const QModelIndex &parent) const
{
    return m_accounts.count();
}

QVariant AccountManager::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_accounts[index.row()]->displayName();
    }

    return QVariant();
}

void AccountManager::dataChangedSlot(bool saveData)
{
    if(saveData) {
        save();
    }
    
    dataChanged(index(m_accounts.size()-1),index(m_accounts.size()-1));
}

void AccountManager::connectAccounts()
{
    for(auto a: m_accounts) {
        a->connectToServer();
    }
}

void AccountManager::changeStatus(Status *status)
{
    for(auto a: m_accounts) {
        a->setStatus(status);
    }
}

void AccountManager::save() const
{
    QSettings settings;
    
    settings.remove("accounts/list/");
    
    if(!m_accounts.isEmpty()) {
        settings.beginWriteArray("accounts/list/", m_accounts.size());
    
        int i=0;
    
        for(auto a: m_accounts) {
            settings.setArrayIndex(i++);
            settings.setValue("id", a->id());
            settings.setValue("type", a->type());
        }
    
        settings.endArray();
    }
}

void AccountManager::load()
{
    QSettings settings;

    int size = settings.beginReadArray("accounts/list/");

    for(int i=0; i<size; ++i) {
        settings.setArrayIndex(i);

        QString type = settings.value("type").toString();
        
        ProtocolPlugin *plugin = m_app->protocolPlugin(type);

        Account *account = plugin->createAccount();

        account->setId(settings.value("id").toString());
        account->load();

        account->initAccount();
        
        addAccount(account);
    }

    settings.endArray();
}
