#ifndef STATUS_H
#define STATUS_H

#include <QObject>

class Status : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Online = 0,
        Away,
        Offline,
        Unknown
    };
    
    explicit Status(QObject *parent = 0);
    
    Type getType() const;
    
public slots:
    void setType(Type type);
    
private:
    Type type;
    QString message;
    
};

#endif // STATUS_H
