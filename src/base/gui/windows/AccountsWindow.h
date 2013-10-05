#ifndef ACCOUNTSWINDOW_H
#define ACCOUNTSWINDOW_H

#include <QListView>
#include <QMainWindow>

#include "common.h"

namespace Ui {
class AccountsWindow;
}

class AccountsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountsWindow(ApplicationController *app, QWidget *parent = 0);
    ~AccountsWindow();

public slots:
    void addAccount();
    //void deleteAccount();
    void openAccount(const QModelIndex &index);

private slots:
    void on_addAccount_clicked();
    
    void on_removeAccount_clicked();
    
    void on_close_clicked();
    
private:
    ApplicationController *app;
    Ui::AccountsWindow *ui;
};

#endif // ACCOUNTSWINDOW_H
