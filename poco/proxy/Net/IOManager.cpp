#include <iostream>
#include <cstring>
#include <algorithm>

#include "IOManager.h"
#include "Socket.h"
#include "WorkThread.h"

namespace base
{

IOManager::IOManager() : 
    m_running(true),
    m_thread(new WorkThread("IOThread")),
    m_sockets()
{
    m_thread->start();
    m_thread->postTask(Bind(&IOManager::run, this));
}

IOManager::~IOManager()
{
    m_running = false;
    m_thread->stop();
    delete m_thread;
}

void IOManager::run()
{
    if (m_running)
    {
        Net::Socket::SocketList readable;
        Net::Socket::SocketList writeable;
        Net::Socket::SocketList exceptable;

        std::vector<SocketNode*>::iterator it = m_sockets.begin();
        for (; it != m_sockets.end(); it++)
        {
            SocketNode* node = *it;
            writeable.push_back(node->getSocket());
            readable.push_back(node->getSocket());
            exceptable.push_back(node->getSocket());
        }

        Net::Socket::select(readable, writeable, exceptable, 50000);
        {
            Net::Socket::SocketList::iterator it = readable.begin();
            for (; it != readable.end(); it++)
            {
                (*it)->readEvent();
            }

            it = writeable.begin();
            for (; it != writeable.end(); ++it)
            {
                (*it)->writeEvent();
            }

            it = exceptable.begin();
            for (; it != exceptable.end(); ++it)
            {
                (*it)->exceptEvent();
            }
        }
    }

    m_thread->postTask(Bind(&IOManager::run, this));
}

SocketNode* IOManager::addServerSocket(Net::SocketAddress& addr, SocketHandler *handler)
{
    Net::ServerSocket *socket = new Net::ServerSocket(handler);
    socket->bind(addr, true);
    socket->listen();
    socket->setBlocking(false);

    SocketNode *node = new SocketNode(std::tr1::shared_ptr<Net::Socket>(socket));
    m_thread->postTask(Bind(&IOManager::addSocketNode, this, node));

    return node;
}

//SocketNode* IOManager::addServerSocket(UInt16 port, SocketHandler *handler)
//{
    //std::tr1::shared_ptr<Net::Socket> socket(new Net::ServerSocket(handler));
    //socket->bind(port);
    //socket->listen();
    //socket->setBlocking(false);

    //SocketNode *node = new SocketNode(socket);
    //m_thread->postTask(Bind(&IOManager::addSocketNode, this, node));

    //return node;
//}


SocketNode* IOManager::addClientSocket(Net::SocketAddress &addr, SocketHandler *handler)
{
    Net::StreamSocket *socket = new Net::StreamSocket(handler);
    if (socket->connect(addr) == 0)
    {
        SocketNode *node = new SocketNode(std::tr1::shared_ptr<Net::Socket>(socket));
        m_thread->postTask(Bind(&IOManager::addSocketNode, this, node));

        return node;
    }

    return NULL;
}

SocketNode* IOManager::addMulticastSocket(Net::SocketAddress& addr, SocketHandler *handler)
{
    // TODO: server and client?
    Net::MulticastSocket* socket = new Net::MulticastSocket(handler);
}

bool IOManager::removeSocket(SocketNode* node)
{
    m_thread->postTask(Bind(&IOManager::removeSocketNode, this, node));
}
        
void IOManager::addSocketNode(SocketNode* node)
{
    m_sockets.push_back(node);
}

void IOManager::removeSocketNode(SocketNode* node)
{
    /*close?*/
    m_sockets.erase(std::remove(m_sockets.begin(), m_sockets.end(), node), m_sockets.end());
}

} //namespace
