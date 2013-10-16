#ifndef PERSON_H
#define PERSON_H

#include <QObject>

#include "common.h"

#include "Status.h"

class Person : public QObject {
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);
    explicit Person(const QString &id, QObject *parent = nullptr);
    ~Person();
    
    virtual QString id() const;
    virtual QString displayName() const;
    virtual Status *status();

signals:
    void statusChanged(Status *status);

public slots:
    virtual void setId(const QString &m_id);
    virtual void setStatus(Status *m_status);

protected:
    QString m_id;
    QString m_nickname;
    Status *m_status;
};

#endif // PERSON_H
