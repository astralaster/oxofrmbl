#ifndef PERSON_H
#define PERSON_H

#include <QObject>

#include "base/Status.h"
#include "common.h"

class Person : public QObject {
    Q_OBJECT
public:
    explicit Person(QObject *parent) : QObject(parent){}
    explicit Person(const QString &nickname, QObject *parent) : QObject(parent), nickname(nickname){}
    
    virtual QString getId() const = 0;

    virtual QString getDisplayName() const {
        return nickname.isEmpty() ? getId() : nickname;
    }

    virtual Status *getStatus() {
        return status;
    }

signals:
    void statusChanged(Status *status);

public slots:
    virtual void setStatus(Status *status) {
        this->status = status;
        emit statusChanged(status);
    }

protected:
    Status *status = nullptr;
    QString nickname;
};

#endif // PERSON_H
