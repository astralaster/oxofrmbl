#include "Status.h"

Status::Status(QObject *parent) :
    QObject(parent)
{
}

Status::Type Status::getType() const
{
    return type;
}

void Status::setType(Status::Type type)
{
    this->type = type;
}
