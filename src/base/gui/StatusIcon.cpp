#include "StatusIcon.h"

StatusIcon::StatusIcon()
{
}

QIcon StatusIcon::forStatus(Status *status)
{
    switch(status->getType()) {
    case Status::Away:
        return QIcon::fromTheme("user-away");
        break;
        
    case Status::Offline:
        return QIcon::fromTheme("user-offline");
        break;
        
    case Status::Online:
    default:
        return QIcon::fromTheme("user-available");
        break;
    }
}
