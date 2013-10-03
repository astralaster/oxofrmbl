#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include "base/ApplicationController.h"

class Plugin {
public:
    virtual ~Plugin() {}
    
    virtual void init(ApplicationController *app) = 0;
};

Q_DECLARE_INTERFACE(Plugin, "com.oxofrmbl/plugins/Plugin/1.0")

#endif // PLUGININTERFACE_H
