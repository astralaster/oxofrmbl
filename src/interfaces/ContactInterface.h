#ifndef CONTACTINTERFACE_H
#define CONTACTINTERFACE_H

#include "base/Account.h"
#include "PersonInterface.h"

class ContactInterface : public PersonInterface
{
public:
    //ContactInterface(Account *acc = nullptr);
    virtual ~ContactInterface() {}
};

Q_DECLARE_INTERFACE(ContactInterface, "com.oxofrmbl/base/ContactInterface/1.0")


#endif // CONTACTINTERFACE_H
