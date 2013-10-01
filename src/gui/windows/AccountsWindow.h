#ifndef ACCOUNTSWINDOW_H
#define ACCOUNTSWINDOW_H

#include <QListView>
#include <QMainWindow>

#include "base/AccountManager.h"

namespace Ui {
class AccountsWindow;
}

class AccountsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountsWindow(AccountManager *manager, QWidget *parent = 0);
    ~AccountsWindow();

public slots:
    void openAccount(const QModelIndex &index);


private slots:
    void on_addAccount_clicked();

private:
    AccountManager *manager;
    Ui::AccountsWindow *ui;
};

#endif // ACCOUNTSWINDOW_H
