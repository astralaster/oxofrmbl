#include "FileTransfer.h"

FileTransfer::FileTransfer(ChatSession *session, bool incoming, const QString &fileName) :
    FileTransfer(session, incoming, fileName, QDateTime())
{

}

FileTransfer::FileTransfer(ChatSession *session, bool incoming, const QString &fileName, const QDateTime &time) :
    ChatMessage(session, incoming, fileName, time)
{

}

QString FileTransfer::fileName()
{
    return body();
}


void FileTransfer::accept(const QString &fileName)
{
    emit accepted(fileName);
}

void FileTransfer::refuse()
{
    emit aborted();
}
