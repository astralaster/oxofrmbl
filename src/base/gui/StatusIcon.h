#ifndef STATUSICON_H
#define STATUSICON_H

#include <QIcon>

#include "common.h"

class StatusIcon
{
public:
    StatusIcon();
    
    static QIcon forStatus(Status *status);
};

#endif // STATUSICON_H
