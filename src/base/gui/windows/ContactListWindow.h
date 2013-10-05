#ifndef CONTACTLISTWINDOW_H
#define CONTACTLISTWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QComboBox>

#include "common.h"

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
    void statusChanged(Status *status);
    
public slots:
    void addContactList(ContactList *cl);
    void removeContactList(ContactList *cl);

private slots:
    void closeEvent(QCloseEvent *e) override;
    void on_status_currentIndexChanged(int index);

private:
    QMap<ContactList*, ContactListWidget*> contactLists;
    Ui::ContactListWindow *ui;
};

#endif // CONTACTLISTWINDOW_H
