#ifndef CONTACTLISTWINDOW_H
#define CONTACTLISTWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QComboBox>

#include "base/Account.h"
#include "base/ContactList.h"

#include "gui/GuiController.h"

class GuiController;

namespace Ui {
class ContactListWindow;
}

class ContactListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ContactListWindow(GuiController *controller, QWidget *parent = 0);
    ~ContactListWindow();

    QComboBox *getStatusSelect();

signals:
    void statusChanged(Account::Status status);
    
public slots:
    void addContactList(ContactList *cl);

private slots:
    void closeEvent(QCloseEvent *e) override;

    void on_status_currentIndexChanged(int index);

private:
    Ui::ContactListWindow *ui;
};

#endif // CONTACTLISTWINDOW_H
