#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QMap>

#include "common.h"

#include "AccountManager.h"
#include "Account.h"
#include "Contact.h"

#include "gui/GuiController.h"

#include "interfaces/ProtocolPluginInterface.h"

class AccountManager;
class ProtocolPlugin;
class GuiController;

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = nullptr);

    AccountManager *accountManager();
    
    QList<QString> protocolPluginNames() const;
    ProtocolPlugin *protocolPlugin(const QString &protocol);
    
signals:
    void terminated();
    
public slots:
    void quit();
    void discoverPlugins();

private:
    QMap<QString, ProtocolPlugin*> protocolPlugins;
    
    GuiController *m_gui = nullptr;
    AccountManager *m_accountManager = nullptr;

};

#endif // APPLICATIONCONTROLLER_H
