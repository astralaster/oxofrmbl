#include "StatusIcon.h"



#include "base/Status.h"

StatusIcon::StatusIcon()
{
}

QIcon StatusIcon::forStatus(Status *status)
{
    switch(status->type()) {
    case Status::Away:
        return QIcon::fromTheme("user-away");
        break;
        
    case Status::Online:
        return QIcon::fromTheme("user-available");
        break;
        
    case Status::Offline:
    default:
        return QIcon::fromTheme("user-offline");
        break;
    }
}
