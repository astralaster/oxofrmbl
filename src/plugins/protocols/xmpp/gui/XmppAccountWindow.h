#ifndef XMPPACCOUNTWINDOW_H
#define XMPPACCOUNTWINDOW_H

#include <QDialog>

#include "base/AccountManager.h"
#include "plugins/protocols/xmpp/XmppAccount.h"

namespace Ui {
class XmppAccountWindow;
}

class XmppAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit XmppAccountWindow(AccountManager *accountManager, XmppAccount *account = nullptr, QWidget *parent = 0);
    ~XmppAccountWindow();

private slots:
    void accept() override;

private:
    XmppAccount *account;
    AccountManager *accountManager;
    Ui::XmppAccountWindow *ui;
};

#endif // XMPPACCOUNTWINDOW_H
