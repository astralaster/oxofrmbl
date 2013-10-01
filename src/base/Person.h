#ifndef PERSON_H
#define PERSON_H

#include <QObject>

#include "common.h"

class Person : public QObject {
    Q_OBJECT

public:
    enum Status
    {
        Online = 0,
        Away,
        Offline,
        Unknown
    };

    explicit Person(QObject *parent) : QObject(parent){}
    explicit Person(const QString &nickname, QObject *parent) : QObject(parent), nickname(nickname){}

    virtual QString getId() const = 0;

    virtual QString getDisplayName() const {
        return nickname.isEmpty() ? getId() : nickname;
    }

    Status getStatus() const {
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
