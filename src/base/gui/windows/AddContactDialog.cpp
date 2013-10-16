#include "AddContactDialog.h"
#include "ui_AddContactDialog.h"

AddContactDialog::AddContactDialog(AccountList *accounts, QWidget *parent) :
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
    auto manager = qobject_cast<AccountList*>(ui->accountComboBox->model());
    return manager->accountAt(ui->accountComboBox->currentIndex());
}
