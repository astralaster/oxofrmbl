#ifndef PERSON_H
#define PERSON_H

#include <QObject>

#include "common.h"

class Person : public QObject {
    Q_OBJECT
public:
    explicit Person(QObject *parent);
    explicit Person(const QString &nickname, QObject *parent);
    
    virtual QString getId() const = 0;

    virtual QString getDisplayName() const;

    virtual Status *getStatus();

signals:
    void statusChanged(Status *status);

public slots:
    virtual void setStatus(Status *status);

protected:
    Status *status;
    QString nickname;
};

#endif // PERSON_H
