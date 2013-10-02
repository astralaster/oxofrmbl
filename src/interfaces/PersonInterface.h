#ifndef PERSONINTERFACE_H
#define PERSONINTERFACE_H

#include <QtPlugin>

class PersonInterface {
public:
    enum Status
    {
        Online = 0,
        Away,
        Offline,
        Unknown
    };

    virtual ~PersonInterface() {}

    virtual QString getId() const = 0;
    virtual QString getDisplayName() const = 0;
    virtual void setStatus(Status status) = 0;
};

Q_DECLARE_INTERFACE(PersonInterface, "com.oxofrmbl/base/PersonInterface/1.0")

#endif // PERSONINTERFACE_H
