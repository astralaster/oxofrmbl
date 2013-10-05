#include "Person.h"

#include "base/Status.h"

Person::Person(QObject *parent) : Person("", parent)
{

}

Person::Person(const QString &nickname, QObject *parent) : QObject(parent), status(new Status()), nickname(nickname)
{

}

QString Person::getDisplayName() const {
    return nickname.isEmpty() ? getId() : nickname;
}

Status *Person::getStatus() {
    return status;
}

void Person::setStatus(Status *status) {
    this->status = status;
    emit statusChanged(status);
}

