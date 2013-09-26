#ifndef CONTACTLISTWINDOW_H
#define CONTACTLISTWINDOW_H

#include <QListView>
#include <QMainWindow>

namespace Ui {
class ContactListWindow;
}

class ContactListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ContactListWindow(QWidget *parent = 0);
    ~ContactListWindow();

    QListView *getList();

signals:
    void windowClosed(int retcode=0);

private slots:
    void closeEvent(QCloseEvent *e) override;

    void on_contactList_doubleClicked(const QModelIndex &index);

private:
    Ui::ContactListWindow *ui;
};

#endif // CONTACTLISTWINDOW_H
