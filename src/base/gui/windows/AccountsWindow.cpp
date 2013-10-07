#include "AccountsWindow.h"
#include "ui_AccountsWindow.h"

#include <QMenu>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>

#include "base/Account.h"
#include "base/AccountManager.h"
#include "base/ApplicationController.h"

#include "interfaces/ProtocolPluginInterface.h"

AccountsWindow::AccountsWindow(ApplicationController *app, QWidget *parent) :
    QMainWindow(parent), app(app),
    ui(new Ui::AccountsWindow)
{
    ui->setupUi(this);

    ui->accountsList->installEventFilter(this);
    ui->accountsList->setModel(app->accountManager());

    connect(ui->accountsList, &QListView::doubleClicked, this, &AccountsWindow::openAccountAtIndex);
}

AccountsWindow::~AccountsWindow()
{
    delete ui;
}

void AccountsWindow::addAccount(/*const QString &protocol*/)
{
    QString protocol = qobject_cast<QAction*>(QObject::sender())->text();
    ProtocolPlugin *plugin = app->protocolPlugin(protocol);
    
    auto account = plugin->createAccount();
    
    auto accountWindow = plugin->createAccountWindow(account);
    
    if(accountWindow->exec() == QDialog::Accepted) {
        app->accountManager()->addAccount(account);
    } else {
        delete account;
    }
}

void AccountsWindow::removeSelectedAccount()
{
    removeAccountAtIndex(ui->accountsList->currentIndex());
}

void AccountsWindow::removeAccountAtIndex(const QModelIndex &index)
{
    auto account = dynamic_cast<Account*>(app->accountManager()->account(index.row()));
    
    if(QMessageBox::question(this, "Delete Account", QString("Are you sure, that you want to delete %1?").arg(account->id())) == QMessageBox::Yes) {
        app->accountManager()->removeAccount(account);
    }
}

void AccountsWindow::openAccountAtIndex(const QModelIndex &index)
{
    auto account = dynamic_cast<Account*>(app->accountManager()->account(index.row()));
    
    ProtocolPlugin *plugin = app->protocolPlugin(account->type());
    
    plugin->createAccountWindow(account);
}

void AccountsWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete) {
        event->accept();
        
        return;
    }
    
    event->ignore();
}

void AccountsWindow::on_addAccount_clicked()
{
    QMenu *menu = new QMenu(this);
    
    for(auto a: app->protocolPluginNames()) {
        menu->addAction(a, this, SLOT(addAccount()));
    }
    
    ui->addAccount->setMenu(menu);
    ui->addAccount->showMenu();
    
}

void AccountsWindow::on_removeAccount_clicked()
{
    removeSelectedAccount();
}

void AccountsWindow::on_close_clicked()
{
    close();
}
