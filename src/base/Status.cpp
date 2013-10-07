#include "Status.h"

Status::Status(QObject *parent) :
    QObject(parent)
{
}

Status::Type Status::type() const
{
    return m_type;
}

void Status::setType(Status::Type type)
{
    m_type = type;
}
