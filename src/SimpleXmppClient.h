#ifndef SIMPLEXMPPCLIENT_H
#define SIMPLEXMPPCLIENT_H

#include "QXmppClient.h"

class SimpleXmppClient : public QObject
{
    Q_OBJECT

public:
    SimpleXmppClient();

public slots:
    void connectToServer(QString address, QString port);
    void sendMessage(QString to, QString message);

private slots:
    void connectedSlot();

signals:
    void connected();

private:
    QXmppClient *client;
};

#endif // SIMPLEXMPPCLIENT_H
