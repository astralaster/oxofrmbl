#include "mainwindow.h"
#include <QApplication>

#include <QPushButton>

#include "plugins/protocols/xmpp/SimpleXmppClient.h"

#include "QXmppClient.h"
#include "QXmppLogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ChatClient *client = new SimpleXmppClient();

    w.connect(&w, SIGNAL(connectToServer(QString,QString,QString)), client, SLOT(connectToServer(QString,QString,QString)));
    w.connect(&w, SIGNAL(sendMessage(const ChatMessage &)), client, SLOT(sendMessage(const ChatMessage &)));

    client->connect(client, SIGNAL(connected()), &w, SLOT(connected()));
    client->connect(client, SIGNAL(messageReceived(QString)), &w, SLOT(messageReceived(QString)));

    
    return a.exec();
}
