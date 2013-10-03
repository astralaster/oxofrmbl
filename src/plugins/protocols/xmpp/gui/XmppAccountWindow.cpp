#include "XmppAccountWindow.h"
#include "ui_XmppAccountWindow.h"

#include <QDialogButtonBox>

XmppAccountWindow::XmppAccountWindow(XmppPlugin *plugin, XmppAccount *account, QWidget *parent) :
    QDialog(parent), plugin(plugin), account(account), 
    ui(new Ui::XmppAccountWindow)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &XmppAccountWindow::accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &XmppAccountWindow::close);

    connect(this, &XmppAccountWindow::accepted, this, &XmppAccountWindow::accept);

    ui->username->setText(account->getUser());
    ui->server->setText(account->getServer());
    ui->password->setText(account->getPassword());
    ui->resource->setText(account->getResource());
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
    account->connectToServer();

    close();
}
