#include "AccountsWindow.h"
#include "ui_AccountsWindow.h"

#include <QMenu>

#include "base/AccountManager.h"
#include "plugins/protocols/xmpp/gui/XmppAccountWindow.h"

AccountsWindow::AccountsWindow(ApplicationController *app, QWidget *parent) :
    QMainWindow(parent), app(app),
    ui(new Ui::AccountsWindow)
{
    ui->setupUi(this);

    ui->accountsList->setModel(app->getAccountManager());

    connect(ui->accountsList, &QListView::doubleClicked, this, &AccountsWindow::openAccount);
}

AccountsWindow::~AccountsWindow()
{
    delete ui;
}

void AccountsWindow::addAccount(/*const QString &protocol*/)
{
    QString protocol = qobject_cast<QAction*>(QObject::sender())->text();
    ProtocolPlugin *plugin = app->getProtocolPlugin(protocol);
    
    auto account = plugin->createAccount();
    
    app->getAccountManager()->addAccount(account);
    
    plugin->showAccountWindow(account);
}

void AccountsWindow::openAccount(const QModelIndex &index)
{
    auto account = dynamic_cast<Account*>(app->getAccountManager()->getAccount(index.row()));
    
    ProtocolPlugin *plugin = app->getProtocolPlugin(account->getType());
    
    plugin->showAccountWindow(account);
}

void AccountsWindow::on_addAccount_clicked()
{
    QMenu *menu = new QMenu(this);
    
    for(auto a: app->getProtocolPluginNames()) {
        menu->addAction(a, this, SLOT(addAccount()));
    }
    
    ui->addAccount->setMenu(menu);
    ui->addAccount->showMenu();
    
}

void AccountsWindow::on_removeAccount_clicked()
{
    auto index = ui->accountsList->currentIndex();
    
    auto account = dynamic_cast<Account*>(app->getAccountManager()->getAccount(index.row()));
    
    app->getAccountManager()->removeAccount(account);
}

void AccountsWindow::on_close_clicked()
{
    close();
}
