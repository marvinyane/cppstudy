#include "IOManager.h"

#include "../Foundation/WorkThread.h"
#include <iostream>
#include <cstring>

namespace base
{

IOManager::IOManager()
{
    m_running = true;

    m_thread = new WorkThread;
    m_thread->start();

    m_thread->postTask(Bind(&IOManager::run, this));
}

IOManager::~IOManager()
{
    m_running = false;

    m_thread->stop();
    m_thread->wait(3000);

    delete m_thread;
}

void IOManager::run()
{
    Poco::Timespan m_timeout(3000);

    while(m_running)
    {
        /**/
        Poco::Net::Socket::SocketList readable;
        Poco::Net::Socket::SocketList writeable;
        Poco::Net::Socket::SocketList exceptable;

        std::vector<SocketNode*>::iterator it = m_sockets.begin();
        for (; it != m_sockets.end(); it++)
        {
            SocketNode* node = *it;
            if (node->m_write.size())
            {
                int length = 0;
                char* str = node->m_write.pop(&length);
                node->m_socket.impl()->sendBytes(str, length);
                delete [] str;
            }

            readable.push_back(node->m_socket);
        }

        if (Poco::Net::Socket::select(readable, writeable, exceptable, m_timeout))
        {
            Poco::Net::Socket::SocketList::iterator it = readable.begin();
            for (; it != readable.end(); it++)
            {
                Poco::Net::Socket s = *it;
                char buffer[1000];
                memset(buffer, 0, sizeof(buffer));

                int len = s.impl()->receiveBytes(buffer, 1000);

                SocketNode* node = searchSocketNode(s);
                node->m_read.push(buffer, len);

                node->m_handler->getWorkThread()->postTask(Bind(&SocketHandler::readReady, node->m_handler, s));
            }
        }
    }
}

bool IOManager::addSocket(Poco::Net::Socket &socket, SocketHandler *handler)
{
    addSocketNode(socket, handler);
}

int IOManager::readSocket(Poco::Net::Socket &socket, char* s, int length)
{
    int readLen = 0;
    SocketNode* node = searchSocketNode(socket);

    char* tmp = node->m_read.pop(&readLen);

    memcpy(s, tmp, readLen);
    return readLen;
}

int IOManager::writeSocket(Poco::Net::Socket &socket, const char* s, int length)
{
    SocketNode* node = searchSocketNode(socket);

    node->m_write.push(s, length);

    return length;
}


void IOManager::addSocketNode(Poco::Net::Socket &socket, SocketHandler *handler)
{
    SocketNode* node = new SocketNode(socket, handler);
    m_sockets.push_back(node);
}

void IOManager::deleteSocketNode(Poco::Net::Socket &socket)
{
    std::vector<SocketNode*>::iterator it = m_sockets.begin();

    for (; it != m_sockets.end(); it++)
    {
        if ((*it)->m_socket == socket)
        {
            m_sockets.erase(it);
            break;
        }
    }
}

IOManager::SocketNode* IOManager::searchSocketNode(Poco::Net::Socket &socket)
{
    std::vector<SocketNode*>::iterator it = m_sockets.begin();

    for (; it != m_sockets.end(); it++)
    {
        if ((*it)->m_socket == socket)
        {
            return *it;
        }
    }

    return NULL;
}

} //namespace
