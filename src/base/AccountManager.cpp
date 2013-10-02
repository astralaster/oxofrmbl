#include "AccountManager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QSettings>

AccountManager::AccountManager(QObject *parent) : QAbstractListModel(parent)
{
}

Account *AccountManager::getAccount(int index)
{
    return accounts[index];
}

void AccountManager::addAccount(Account *a)
{
    accounts << a;
    emit dataChanged(index(accounts.size()-1),index(accounts.size()-1));
}

QList<Account *> AccountManager::getAccounts() const
{
    return accounts;
}

int AccountManager::rowCount(const QModelIndex &parent) const
{
    /*int result = 0;

    for(auto a : accounts) {
        result += a->getContacts()->count();
    }

    return result;*/
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

        a->save();
    }

    settings.endArray();
}

void AccountManager::load()
{
    QSettings settings;

    int size = settings.beginReadArray("accounts/list/");

    QDir path(QApplication::applicationDirPath());
    path.cd("plugins/protocols/");

    for(int i=0; i<size; ++i) {
        settings.setArrayIndex(i);

        QString type = settings.value("type").toString();

        path.cd(type);

        QPluginLoader loader(path.absoluteFilePath(QString("lib%1_plugin.so").arg(type)));

        auto account = new Account();

        AccountInterface *object = qobject_cast<AccountInterface*>(loader.instance());

        account->setAccountObject(object);

        account->setId(settings.value("id").toString());
        account->load();

        account->initAccount();

        accounts.append(account);
    }

    settings.endArray();
}