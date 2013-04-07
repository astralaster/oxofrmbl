#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

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
}

void MainWindow::on_connectButton_clicked()
{
    emit connectToServer(ui->usernameEdit->text() +"@"+ui->addressEdit->text(), ui->passwordEdit->text());
}

void MainWindow::on_sendButton_clicked()
{
    emit sendMessage(ui->receiverEdit->text(), ui->messageEdit->toPlainText());
}
