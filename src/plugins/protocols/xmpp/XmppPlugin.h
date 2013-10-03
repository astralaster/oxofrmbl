#ifndef XMPPPLUGIN_H
#define XMPPPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "interfaces/ProtocolPluginInterface.h"
#include "XmppAccount.h"

class XmppPlugin : public QObject, public ProtocolPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.oxofrmbl/protocols/xmpp/")
    Q_INTERFACES(ProtocolPlugin)
    
signals:
    void accountCreated();
    
public:
    explicit XmppPlugin(QObject *parent = 0);
    
    XmppAccount *createAccount() override;
    void showAccountWindow(Account *account = nullptr) override;
    
public slots:
    void init(ApplicationController *app) override;

private:
    ApplicationController *app;
    
};

#endif // XMPPPLUGIN_H
