#ifndef PROTOCOLPLUGININTERFACE_H
#define PROTOCOLPLUGININTERFACE_H

#include "common.h"
#include "AccountInterface.h"
#include "PluginInterface.h"

class ProtocolPlugin : public Plugin {
public:
    virtual ~ProtocolPlugin() {}
    
    virtual AccountInterface *createAccount() = 0;
    
    virtual void showAccountWindow(Account *account = nullptr) = 0;
};

Q_DECLARE_INTERFACE(ProtocolPlugin, "com.oxofrmbl/plugins/ProtocolPlugin/1.0")

#endif // PROTOCOLPLUGININTERFACE_H
