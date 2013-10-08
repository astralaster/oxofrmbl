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
    
public:
    explicit XmppPlugin(QObject *parent = nullptr);
    
    Account *createAccount() override;
    QDialog *createAccountWindow(Account *account) override;
    
public slots:
    void init(ApplicationController *m_app) override;

private:
    ApplicationController *m_app = nullptr;
    
};

QXmppPresence &operator<<(QXmppPresence &presence, const Status &status);
Status &operator<<(Status &status, const QXmppPresence &presence);

#endif // XMPPPLUGIN_H
