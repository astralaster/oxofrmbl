#ifndef PERSONINTERFACE_H
#define PERSONINTERFACE_H

#include <QtPlugin>

#include "base/Status.h"

class PersonInterface {
public:
    virtual ~PersonInterface() {}

    virtual QString getId() const = 0;
    virtual QString getDisplayName() const = 0;
};

Q_DECLARE_INTERFACE(PersonInterface, "com.oxofrmbl/base/PersonInterface/1.0")

#endif // PERSONINTERFACE_H
