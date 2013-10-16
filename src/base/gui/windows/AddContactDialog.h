#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QDialog>

#include "common.h"

#include "../AccountList.h"
#include "base/AccountManager.h"
#include "base/Account.h"

namespace Ui {
class AddContactDialog;
}

class AddContactDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddContactDialog(AccountList *accounts, QWidget *parent = nullptr);
    ~AddContactDialog();
    
    QString getId() const;
    Account *getAccount();
    
private:
    AccountList *accounts;
    Ui::AddContactDialog *ui;
};

#endif // ADDCONTACTDIALOG_H
