#ifndef CONTACTLISTWINDOW_H
#define CONTACTLISTWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QComboBox>

#include "base/Account.h"
#include "base/ContactList.h"

namespace Ui {
class ContactListWindow;
}

class ContactListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ContactListWindow(ContactList *contacts, QWidget *parent = 0);
    ~ContactListWindow();

    QComboBox *getStatusSelect();

signals:
    void statusChanged(Account::Status status);

private slots:
    void closeEvent(QCloseEvent *e) override;

    void on_contactList_doubleClicked(const QModelIndex &index);
    void on_status_currentIndexChanged(int index);

private:
    Ui::ContactListWindow *ui;
};

#endif // CONTACTLISTWINDOW_H
