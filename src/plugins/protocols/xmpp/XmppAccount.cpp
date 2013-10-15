#include "XmppAccount.h"

#include <QSettings>

#include <qxmpp/QXmppRosterManager.h>

#include "base/ChatMessage.h"

#include "XmppPlugin.h"
#include "XmppContact.h"


XmppAccount::XmppAccount()
{

}

XmppAccount::~XmppAccount()
{
    delete m_client;
}

void XmppAccount::initAccount()
{
    m_client = new QXmppClient();

    m_client->logger()->setLoggingType(QXmppLogger::StdoutLogging);

    auto transferManager = new QXmppTransferManager();
    //transferManager->setProxy("proxy.qxmpp.org");

    m_client->addExtension(transferManager);

    connect(transferManager, &QXmppTransferManager::fileReceived, this, &XmppAccount::fileReceivedSlot);
    
    connect(m_client, &QXmppClient::error, this, &Account::error);

    connect(&m_client->rosterManager(), &QXmppRosterManager::rosterReceived, this, &XmppAccount::retrieveContacts, Qt::DirectConnection);
    connect(&m_client->rosterManager(), &QXmppRosterManager::subscriptionReceived, this, &XmppAccount::subscriptionReceivedSlot);
    
    connect(m_client, &QXmppClient::messageReceived, this, &XmppAccount::messageReceivedSlot);
    connect(m_client, &QXmppClient::iqReceived, this, &XmppAccount::iqReceivedSlot);
    connect(m_client, &QXmppClient::presenceReceived, this, &XmppAccount::presenceReceivedSlot);
    
    connect(m_client, &QXmppClient::disconnected, this, &XmppAccount::disconnected);
    connect(this, &XmppAccount::disconnected, this, &XmppAccount::clearContacts);
}

void XmppAccount::retrieveContacts()
{
    for(auto contact_jid: m_client->rosterManager().getRosterBareJids())
    {
        /*auto presences = m_client->rosterManager().getAllPresencesForBareJid(contact_jid);
        for(QXmppPresence p: presences.values()) {
            qDebug() << p.from();
        }
        
        auto resources = m_client->rosterManager().getResources(contact_jid);*/
        
        auto type = m_client->rosterManager().getRosterEntry(contact_jid).subscriptionType();
        if(type == QXmppRosterIq::Item::From || type == QXmppRosterIq::Item::None ||
                type == QXmppRosterIq::Item::NotSet || type == QXmppRosterIq::Item::Remove)
        {

        } else {
            Account::addContact(new XmppContact(this, contact_jid));
        }
    }

    emit connected();
}

void XmppAccount::remove()
{
    m_client->disconnectFromServer();
    QSettings().remove(QString("accounts/xmpp/%1/").arg(id()));
}

void XmppAccount::save() const
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(id()));

    settings.setValue("server", m_server);
    settings.setValue("user", m_user);
    settings.setValue("password", m_password);
    settings.setValue("resource", m_resource);
    settings.setValue("priority", m_priority);

    settings.endGroup();
    
    emit accountSaved();
}

void XmppAccount::load()
{
    QSettings settings;

    settings.beginGroup(QString("accounts/xmpp/%1/").arg(id()));

    m_server = settings.value("server", m_server).toString();
    m_user = settings.value("user", m_user).toString();
    m_password = settings.value("password", m_password).toString();
    m_resource = settings.value("resource", m_resource).toString();
    m_priority = settings.value("priority", m_priority).toInt();

    settings.endGroup();
}

QString XmppAccount::server() const
{
    return m_server;
}

QString XmppAccount::user() const
{
    return m_user;
}

QString XmppAccount::password() const
{
    return m_password;
}

QString XmppAccount::resource() const
{
    return m_resource;
}

int XmppAccount::priority() const
{
    return m_priority;
}

QString XmppAccount::type() const
{
    return "xmpp";
}

QString XmppAccount::id() const
{
    if(m_id.isEmpty()) {
        return m_user+"@"+m_server;
    } else {
        return m_id;
    }
}

QString XmppAccount::displayName() const
{
    return id();
}

void XmppAccount::connectToServer()
{
    if(!isConnected()) {
        m_client->connectToServer(m_user+"@"+m_server+"/"+m_resource, m_password);
    }
}

void XmppAccount::disconnectFromServer()
{
    if(isConnected()) {
        m_client->disconnectFromServer();
        emit disconnected();
    }
}

void XmppAccount::sendMessage(ChatMessage *msg)
{
    m_client->sendMessage(msg->contact()->id(), msg->body());
}

void XmppAccount::sendStateUpdate(const Contact *contact, ChatSession::State state)
{
    // TODO can't touch this
    //QXmppDiscoveryManager *ext = m_client->findExtension<QXmppDiscoveryManager>();
    //m_client->sendMessage(session->contact()->id(), );
    
    QXmppMessage message(id(), contact->id());
    
    QXmppMessage::State xmppState;
    xmppState << state;
    
    message.setState(xmppState);
    
    m_client->sendPacket(message);
}

void XmppAccount::initFileTransfer(FileTransfer *fileTransfer)
{
    auto transferManager = m_client->findExtension<QXmppTransferManager>();

    if(transferManager != nullptr)
    {
        auto job = transferManager->sendFile(fileTransfer->contact()->id(), fileTransfer->fileName());

        setupFileTransfer(fileTransfer, job);
    }
}

ChatSession *XmppAccount::startSession(Contact *contact)
{
    auto chatSession = session(contact->id());
    
    if(chatSession == nullptr)
    {
        auto from = XmppContact::parseJabberId(contact->id());
        
        if(from[2].isEmpty()) {
            auto fromJid = from[0]+"@"+from[1];
            
            QRegExp pattern(QRegExp::escape(fromJid)+"/(.+)");
            
            auto s = sessions(pattern);
            
            if(!s.isEmpty()) {
                chatSession = s.first();
            }
        }
    }
    
    return Account::startSession(contact);
}

void XmppAccount::setState(const QString &server, const QString &user, const QString &password, const QString &resource, int priority)
{
    setServer(server);
    setUser(user);
    setPassword(password);
    setResource(resource);
    setPriority(priority);
}

void XmppAccount::setServer(const QString &server)
{
    m_server = server;
}

void XmppAccount::setUser(const QString &user)
{
    m_user = user;
}

void XmppAccount::setPassword(const QString &password)
{
    m_password = password;
}

void XmppAccount::setResource(const QString &resource)
{
    m_resource = resource;
}

void XmppAccount::setPriority(int priority)
{
    m_priority = priority;
}

void XmppAccount::setStatus(Status *status)
{
    QXmppPresence presence;

    presence << *status;

    m_client->setClientPresence(presence);

    if(presence.type() == QXmppPresence::Unavailable) {
        disconnectFromServer();
    }
    
    Account::setStatus(status);
}

void XmppAccount::acceptContact(Contact *contact)
{
    m_client->rosterManager().acceptSubscription(contact->id());
    Account::acceptContact(contact);
}

void XmppAccount::refuseContact(Contact *contact)
{
    m_client->rosterManager().refuseSubscription(contact->id());
    Account::refuseContact(contact);
}

Contact *XmppAccount::createContact(const QString &contactId)
{
    return new XmppContact(this, contactId);
}

void XmppAccount::addContact(Contact *contact)
{
    auto jid = contact->id();
    
    if(m_client->rosterManager().addItem(jid))
    {
        m_client->rosterManager().subscribe(jid);
        //*contact->status() << presence;
        Account::addContact(contact);
    }
}

void XmppAccount::removeContact(Contact *contact)
{
    QString jid = contact->id();
    
    if(m_client->rosterManager().removeItem(jid))
    {
        m_client->rosterManager().unsubscribe(jid);
        m_client->rosterManager().refuseSubscription(jid);
        Account::removeContact(contact);
    }
}

void XmppAccount::fileReceivedSlot(QXmppTransferJob *job)
{
    auto chatSession = findSessionForJid(job->jid());

    if(chatSession != nullptr)
    {
        auto fileTransfer = new FileTransfer(chatSession, true, job->fileName());
        setupFileTransfer(fileTransfer, job);

        emit fileReceived(fileTransfer);
    }
}

void XmppAccount::iqReceivedSlot(const QXmppIq &iq)
{
    //qDebug() << iq.type();
}

void XmppAccount::subscriptionReceivedSlot(const QString &jid)
{
    Contact *c = contact(jid);
    
    if(c == nullptr) {
        c = new XmppContact(this, jid);
    }
    
    emit contactRequestReceived(c);
}

void XmppAccount::messageReceivedSlot(const QXmppMessage &msg)
{
    if(msg.type() != QXmppMessage::Chat)
    {
        return;
    }

    if(msg.state() != QXmppMessage::Inactive)
    {
        auto chatSession = findSessionForJid(msg.from());

        if(chatSession != nullptr)
        {
            if((msg.state() == QXmppMessage::Active || !msg.state()) && !msg.body().isEmpty())
            {
                auto message = new ChatMessage(chatSession, true, msg.body(), msg.stamp());
                emit messageReceived(message);
            }

            ChatSession::State state;
            state = state << msg.state();
            
            emit stateUpdateReceived(chatSession->contact(), state);
        }
    }
}

ChatSession *XmppAccount::findSessionForJid(const QString &jid)
{
    ChatSession *result = nullptr;

    result = session(jid);

    if(result == nullptr) {
        auto jidParts = XmppContact::parseJabberId(jid);
        auto bareJid = QString("%1@%2").arg(jidParts[0], jidParts[1]);

        result = session(bareJid);

        if(result == nullptr) {
            auto contact = new XmppContact(this, jid);
            auto presence = m_client->rosterManager().getPresence(bareJid, jidParts[2]);

            if(presence.type() == QXmppPresence::Available || presence.type() == QXmppPresence::Unavailable) {
                contact->setStatus(&(*contact->status() << presence));
            }

            result = startSession(contact);
        }
    }

    return result;
}

void XmppAccount::setupFileTransfer(FileTransfer *fileTransfer, QXmppTransferJob *job)
{
    connect(job, &QXmppTransferJob::progress, fileTransfer, &FileTransfer::progress);

    connect(fileTransfer, SIGNAL(accepted(QString)), job, SLOT(accept(QString)));
    connect(fileTransfer, &FileTransfer::aborted, job, &QXmppTransferJob::abort);
}


void XmppAccount::presenceReceivedSlot(const QXmppPresence &presence)
{
    auto from = XmppContact::parseJabberId(presence.from());
    auto jid = from[0]+"@"+from[1];
    auto jid_long = jid+"/"+from[2];
    
    if(jid == id()) {
        return;
    }
    
    Contact *contact = nullptr;
    
    for(Contact *c: contacts()) {
        if(c->id() == jid || c->id() == jid_long) {
            contact = c;
            break;
        }
    }
    
    if(contact != nullptr) {
        if(presence.type() == QXmppPresence::Available || presence.type() == QXmppPresence::Unavailable) {
            contact->setStatus(&(*contact->status() << presence));
        }
    }
}
