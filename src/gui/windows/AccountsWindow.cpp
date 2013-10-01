#include "AccountsWindow.h"
#include "ui_AccountsWindow.h"

#include "base/AccountManager.h"
#include "plugins/protocols/xmpp/gui/XmppAccountWindow.h"

AccountsWindow::AccountsWindow(AccountManager *manager, QWidget *parent) :
    QMainWindow(parent), manager(manager),
    ui(new Ui::AccountsWindow)
{
    ui->setupUi(this);

    ui->accountsList->setModel(manager);

    connect(ui->accountsList, &QListView::doubleClicked, this, &AccountsWindow::openAccount);
}

AccountsWindow::~AccountsWindow()
{
    delete ui;
}

void AccountsWindow::openAccount(const QModelIndex &index)
{
    auto account = dynamic_cast<XmppAccount*>(manager->getAccount(index.row()));

    (new XmppAccountWindow(manager, account, this))->show();
}

void AccountsWindow::on_addAccount_clicked()
{
    (new XmppAccountWindow(manager, nullptr, this))->show();
}
