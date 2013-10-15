#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QFile>

#include "ChatMessage.h"

class FileTransfer : public ChatMessage
{
    Q_OBJECT
public:
    FileTransfer(ChatSession *session, bool incoming, const QString &fileName = "");
    FileTransfer(ChatSession *session, bool incoming, const QString &fileName, const QDateTime &time);

    QString fileName();

signals:
    void accepted(const QString &fileName);
    void progress(qint64 done, qint64 total);
    void aborted();
    void finished();

public slots:
    void accept(const QString &fileName);
    void refuse();


};

#endif // FILETRANSFER_H
