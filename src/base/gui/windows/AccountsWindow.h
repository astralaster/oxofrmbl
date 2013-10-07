#ifndef ACCOUNTSWINDOW_H
#define ACCOUNTSWINDOW_H

#include <QListView>
#include <QMainWindow>

#include "common.h"
#include "base/ApplicationController.h"

class ApplicationController;

namespace Ui {
class AccountsWindow;
}

class AccountsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountsWindow(ApplicationController *app, QWidget *parent = nullptr);
    ~AccountsWindow();

public slots:
    void addAccount();
    //void deleteAccount();
    void removeSelectedAccount();
    void removeAccountAtIndex(const QModelIndex &index);
    void openAccountAtIndex(const QModelIndex &index);

private slots:
    void keyPressEvent(QKeyEvent *event) override;
    void on_addAccount_clicked();
    void on_removeAccount_clicked();
    void on_close_clicked();
    
private:
    ApplicationController *app;
    Ui::AccountsWindow *ui;
};

#endif // ACCOUNTSWINDOW_H
