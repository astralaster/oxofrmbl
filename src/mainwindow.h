#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();

signals:
    void connectToServer(QString jabberId, QString password);
    void sendMessage(QString to, QString message);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
