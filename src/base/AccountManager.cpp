#include "AccountManager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QSettings>

#include "Account.h"
#include "ApplicationController.h"
#include "interfaces/ProtocolPluginInterface.h"

AccountManager::AccountManager(ApplicationController *app, QObject *parent) : QAbstractListModel(parent), app(app)
{
    connect(this, &AccountManager::changed, this, &AccountManager::dataChangedSlot);
}

Account *AccountManager::getAccount(int index)
{
    return accounts[index];
}

void AccountManager::addAccount(Account *account, bool saveData)
{
    accounts << account;
    connect(account, &Account::accountSaved, this, &AccountManager::accountSavedSlot);
    
    emit accountAdded(account);
    emit changed(saveData);
}

void AccountManager::removeAccount(Account *account)
{
    emit accountRemoved(account);
    
    accounts.removeOne(account);
    account->remove();
    
    delete account;
    
    emit changed(true);
}

QList<Account *> AccountManager::getAccounts() const
{
    return accounts;
}

int AccountManager::rowCount(const QModelIndex &parent) const
{
    return accounts.count();
}

QVariant AccountManager::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return accounts[index.row()]->getDisplayName();
    }

    return QVariant();
}

void AccountManager::accountSavedSlot()
{
    emit changed(true);
}

void AccountManager::dataChangedSlot(bool saveData)
{
    if(saveData) {
        save();
    }
    
    dataChanged(index(accounts.size()-1),index(accounts.size()-1));
}

void AccountManager::connectAccounts()
{
    for(auto a: accounts) {
        a->connectToServer();
    }
}

void AccountManager::changeStatus(Status *status)
{
    for(auto a: accounts) {
        a->setStatus(status);
    }
}

void AccountManager::save() const
{
    QSettings settings;
    
    settings.remove("accounts/list/");
    
    if(!accounts.isEmpty()) {
        settings.beginWriteArray("accounts/list/", accounts.size());
    
        int i=0;
    
        for(auto a: accounts) {
            settings.setArrayIndex(i++);
            settings.setValue("id", a->getId());
            settings.setValue("type", a->getType());
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
        
        ProtocolPlugin *plugin = app->getProtocolPlugin(type);

        Account *account = plugin->createAccount();

        account->setId(settings.value("id").toString());
        account->load();

        account->initAccount();
        
        addAccount(account);
    }

    settings.endArray();
}
