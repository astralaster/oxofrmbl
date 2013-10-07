#include "AddContactDialog.h"
#include "ui_AddContactDialog.h"

#include "base/AccountManager.h"

AddContactDialog::AddContactDialog(AccountManager *accounts, QWidget *parent) :
    QDialog(parent), accounts(accounts),
    ui(new Ui::AddContactDialog)
{
    ui->setupUi(this);
    ui->accountComboBox->setModel(accounts);
}

AddContactDialog::~AddContactDialog()
{
    delete ui;
}

QString AddContactDialog::getId() const
{
    return ui->idEdit->text();
}

Account *AddContactDialog::getAccount()
{
    auto manager = qobject_cast<AccountManager*>(ui->accountComboBox->model());
    return manager->account(ui->accountComboBox->currentIndex());
}
