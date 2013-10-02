#ifndef PERSON_H
#define PERSON_H

#include <QObject>

#include "interfaces/PersonInterface.h"

#include "common.h"

class Person : public QObject, public PersonInterface {
    Q_OBJECT
    Q_INTERFACES(PersonInterface)
public:
    explicit Person(QObject *parent) : QObject(parent){}
    explicit Person(const QString &nickname, QObject *parent) : QObject(parent), nickname(nickname){}

    virtual QString getDisplayName() const {
        return nickname.isEmpty() ? getId() : nickname;
    }

    virtual Status getStatus() const {
        return status;
    }

signals:
    void statusChanged(Status status);

public slots:
    virtual void setStatus(Status status) {
        this->status = status;
        emit statusChanged(status);
    }

protected:
    Status status;
    QString nickname;
};

#endif // PERSON_H
