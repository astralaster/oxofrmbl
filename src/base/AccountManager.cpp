#include "AccountManager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QSettings>

AccountManager::AccountManager(ApplicationController *app, QObject *parent) : QAbstractListModel(parent), app(app)
{
}

Account *AccountManager::getAccount(int index)
{
    return accounts[index];
}

void AccountManager::addAccount(Account *a)
{
    accounts << a;
    
    connect(a, &Account::accountSaved, this, &AccountManager::save);
    
    emit dataChanged(index(accounts.size()-1),index(accounts.size()-1));
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

void AccountManager::changeStatus(Person::Status status)
{
    for(auto a : accounts) {
        a->setStatus(status);
    }
}

void AccountManager::save() const
{
    QSettings settings;

    settings.beginWriteArray("accounts/list/", accounts.size());

    int i=0;

    for(auto a: accounts) {
        settings.setArrayIndex(i++);
        settings.setValue("id", a->getId());
        settings.setValue("type", a->getType());
    }

    settings.endArray();
}

void AccountManager::load()
{
    QSettings settings;

    int size = settings.beginReadArray("accounts/list/");

    for(int i=0; i<size; ++i) {
        settings.setArrayIndex(i);

        QString type = settings.value("type").toString();
        
        ProtocolPlugin *plugin = app->getProtocolPlugin(type);

        AccountInterface *_account = plugin->createAccount();
        Account *account = _account->getAccountObject();

        account->setId(settings.value("id").toString());
        account->load();

        account->initAccount();
    }

    settings.endArray();
}
