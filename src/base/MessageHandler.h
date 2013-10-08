#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include "common.h"

#include "ChatMessage.h"

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr);
    virtual ~MessageHandler() {}
    
signals:
    
public slots:
    virtual void handleMessage(ChatMessage *msg) = 0;
    
};

#endif // MESSAGEHANDLER_H
