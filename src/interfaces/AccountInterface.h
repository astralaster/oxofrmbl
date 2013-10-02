#ifndef ACCOUNTINTERFACE_H
#define ACCOUNTINTERFACE_H

#include <QtPlugin>

#include "PersonInterface.h"
#include "base/ChatSession.h"

class AccountInterface : public PersonInterface
{
public:
    virtual ~AccountInterface() {}

    virtual void initAccount() = 0;

    virtual QString getType() const = 0;
    virtual void setAccountObject(Account *account) = 0;

    virtual bool connectToServer() = 0;
    virtual void disconnectFromServer() = 0;
    virtual void sendMessage(const ChatMessage *msg) = 0;

    virtual void save() const = 0;
    virtual void load() = 0;
};

Q_DECLARE_INTERFACE(AccountInterface, "com.oxofrmbl/base/AccountInterface/1.0")

#endif // ACCOUNTINTERFACE_H
