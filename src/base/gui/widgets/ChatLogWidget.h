#ifndef CHATLOGWIDGET_H
#define CHATLOGWIDGET_H

#include <QLabel>
#include <QListWidget>
#include <QTextEdit>

#include "common.h"
#include "base/Contact.h"
#include "base/ChatMessage.h"

class ChatLogWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit ChatLogWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setContact(Contact *contact);

    void updateChatState(ChatSession::State state);
    void addMessage(const ChatMessage *msg);

private:
    Contact *m_contact;
    QLabel *m_stateLabel;

};

#endif // CHATLOGWIDGET_H
