#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plugins/protocols/xmpp/XmppContact.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connected()
{
    ui->messageFrame->setEnabled(true);
    ui->connectionFrame->hide();
}

void MainWindow::messageReceived(QString msg)
{
    ui->messageDisplay->setPlainText(ui->messageDisplay->toPlainText()+msg+"\n");
}

void MainWindow::on_connectButton_clicked()
{
    QString address = ui->addressEdit->text();
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    emit connectToServer(address, username, password);
}

void MainWindow::on_sendButton_clicked()
{
    ChatContact *to = new XmppContact(ui->receiverEdit->text());
    ChatMessage msg = ChatMessage(to, ui->messageEdit->toPlainText());

    ui->messageDisplay->setPlainText(ui->messageDisplay->toPlainText()+msg.getBody()+"\n");

    emit sendMessage(msg);
}
