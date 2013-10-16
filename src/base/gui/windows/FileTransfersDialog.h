#ifndef FILETRANSFERSDIALOG_H
#define FILETRANSFERSDIALOG_H

#include <QDialog>

#include "base/FileTransfer.h"

namespace Ui {
class FileTransfersDialog;
}

class FileTransfersDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FileTransfersDialog(QWidget *parent = 0);
    ~FileTransfersDialog();
    
public slots:
    void showTransfer(FileTransfer *transfer);
    void removeTransfer(FileTransfer *transfer);

private:
    QList<FileTransfer*> m_transfers;
    Ui::FileTransfersDialog *ui;
};

#endif // FILETRANSFERSDIALOG_H
