#ifndef XMPPACCOUNTWINDOW_H
#define XMPPACCOUNTWINDOW_H

#include <QDialog>

#include "../XmppPlugin.h"
#include "../XmppAccount.h"

#include "base/AccountManager.h"


namespace Ui {
class XmppAccountWindow;
}

class XmppAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit XmppAccountWindow(XmppPlugin *plugin, XmppAccount *account = nullptr, QWidget *parent = nullptr);
    ~XmppAccountWindow();

private slots:
    void accept() override;

private:
    XmppPlugin *plugin;
    XmppAccount *account;
    Ui::XmppAccountWindow *ui;
};

#endif // XMPPACCOUNTWINDOW_H
