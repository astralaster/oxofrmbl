#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ChatMessage.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connected();
    void messageReceived(QString);

private slots:
    void on_connectButton_clicked();
    void on_sendButton_clicked();

signals:
    void connectToServer(const QString &address, const QString &user, const QString &password);
    void sendMessage(const ChatMessage &msg);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
