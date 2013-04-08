#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

class ChatContact
{
public:
    ChatContact();
    virtual QString getId() const = 0;
    QString getNickname() const {return nickname;}

private:
    QString nickname;
    
};

#endif // CONTACT_H
