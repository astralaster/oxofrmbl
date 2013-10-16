#include "Person.h"

#include "base/Status.h"

Person::Person(QObject *parent) : Person("", parent)
{

}

Person::Person(const QString &id, QObject *parent) :
    QObject(parent), m_id(id), m_status(new Status(this))
{
    
}

Person::~Person()
{
    qDebug() << "~Person";
}

QString Person::id() const
{
    return m_id;
}

QString Person::displayName() const {
    return m_nickname.isEmpty() ? id() : m_nickname;
}

Status *Person::status() {
    return m_status;
}

void Person::setId(const QString &id) {
    this->m_id = id;
}

void Person::setStatus(Status *currentStatus) {
    this->m_status = currentStatus;
    emit statusChanged(currentStatus);
}

