#include "XmppAccountWindow.h"
#include "ui_XmppAccountWindow.h"

#include <QDialogButtonBox>

XmppAccountWindow::XmppAccountWindow(AccountManager *accountManager, XmppAccount *account, QWidget *parent) :
    QDialog(parent), account(account), accountManager(accountManager),
    ui(new Ui::XmppAccountWindow)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &XmppAccountWindow::accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &XmppAccountWindow::close);

    connect(this, &XmppAccountWindow::accepted, this, &XmppAccountWindow::accept);

    if(account != nullptr) {
        ui->username->setText(account->getUser());
        ui->server->setText(account->getServer());
        ui->password->setText(account->getPassword());
        ui->resource->setText(account->getResource());
    }
}

XmppAccountWindow::~XmppAccountWindow()
{
    qDebug() << "~XmppAccountWindow";
    delete ui;
}

void XmppAccountWindow::accept()
{
    if(account == nullptr) {
        auto _account = new Account();
        account = new XmppAccount(_account);
        _account->setAccountObject(account);

        accountManager->addAccount(_account);
    }

    account->setState(ui->server->text(), ui->username->text(), ui->password->text(), ui->resource->text());
    account->save();

    close();
}