#include "mainwindow.h"
#include <QApplication>

#include <QPushButton>

#include "SimpleXmppClient.h"

#include "QXmppClient.h"
#include "QXmppLogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SimpleXmppClient client;

    w.connect(&w, SIGNAL(connectToServer(QString,QString)), &client, SLOT(connectToServer(QString,QString)));
    w.connect(&w, SIGNAL(sendMessage(QString,QString)), &client, SLOT(sendMessage(QString,QString)));
    client.connect(&client, SIGNAL(connected()), &w, SLOT(connected()));
    client.connect(&client, SIGNAL(messageReceived(QString)), &w, SLOT(messageReceived(QString)));

    
    return a.exec();
}
