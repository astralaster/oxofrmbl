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
    
    explicit Status(QObject *parent = nullptr);
    
    Type type() const;
    
public slots:
    void setType(Type type);
    
private:
    Type m_type = Offline;
    QString m_message;
    
};

#endif // STATUS_H
