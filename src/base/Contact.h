#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include "common.h"
#include "Account.h"

class Contact : public QObject
{
    Q_OBJECT
public:
    Contact(Account *acc);

    Account *getAccount();

    virtual QString getId() const = 0;
    virtual QString getDisplayName() const;

protected:
    Account *account;
    QString nickname;
    
};

#endif // CONTACT_H
