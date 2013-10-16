#include "FileTransfersDialog.h"
#include "ui_FileTransfersDialog.h"

FileTransfersDialog::FileTransfersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileTransfersDialog)
{
    ui->setupUi(this);
}

FileTransfersDialog::~FileTransfersDialog()
{
    delete ui;
}

void FileTransfersDialog::showTransfer(FileTransfer *transfer)
{
    m_transfers.append(transfer);
}

void FileTransfersDialog::removeTransfer(FileTransfer *transfer)
{
    m_transfers.removeOne(transfer);
}
