#include "XmppAccountWindow.h"
#include "ui_XmppAccountWindow.h"

#include <QDialogButtonBox>

XmppAccountWindow::XmppAccountWindow(XmppPlugin *plugin, XmppAccount *account, QWidget *parent) :
    QDialog(parent), plugin(plugin), account(account), 
    ui(new Ui::XmppAccountWindow)
{
    ui->setupUi(this);

    ui->username->setText(account->user());
    ui->server->setText(account->server());
    ui->password->setText(account->password());
    ui->resource->setText(account->resource());
}

XmppAccountWindow::~XmppAccountWindow()
{
    delete ui;
}

void XmppAccountWindow::accept()
{
    account->setState(ui->server->text(), ui->username->text(), ui->password->text(), ui->resource->text());
    account->save();
    
    account->initAccount();
    
    // @TODO move away
    account->connectToServer();
    
    QDialog::accept();
}
