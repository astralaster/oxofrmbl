#include "XmppAccountWindow.h"
#include "ui_XmppAccountWindow.h"

#include <QDialogButtonBox>

XmppAccountWindow::XmppAccountWindow(XmppPlugin *plugin, XmppAccount *account, QWidget *parent) :
    QDialog(parent), plugin(plugin), account(account), 
    ui(new Ui::XmppAccountWindow)
{
    ui->setupUi(this);

    ui->usernameEdit->setText(account->user());
    ui->serverEdit->setText(account->server());
    ui->passwordEdit->setText(account->password());
    ui->resourceEdit->setText(account->resource());
    ui->prioritySpinBox->setValue(account->priority());
}

XmppAccountWindow::~XmppAccountWindow()
{
    delete ui;
}

void XmppAccountWindow::accept()
{
    account->setState(
                ui->serverEdit->text(), 
                ui->usernameEdit->text(), 
                ui->passwordEdit->text(), 
                ui->resourceEdit->text(), 
                ui->prioritySpinBox->value()
    );
    
    account->save();
    
    account->initAccount();
    
    // @TODO move away
    account->connectToServer();
    
    QDialog::accept();
}
