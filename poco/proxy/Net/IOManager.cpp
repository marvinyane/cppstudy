#include <iostream>
#include <cstring>

#include "IOManager.h"

namespace base
{

IOManager::IOManager()
{
    m_running = true;

    m_thread = new WorkThread("IOThread");
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
    while(m_running)
    {
        /**/
        Net::Socket::SocketList readable;
        Net::Socket::SocketList writeable;
        Net::Socket::SocketList exceptable;

        std::vector<SocketNode*>::iterator it = m_sockets.begin();
        for (; it != m_sockets.end(); it++)
        {
            SocketNode* node = *it;
            while (node->m_write.size())
            {
                int length = 0;
                char* str = node->m_write.pop(&length);
                int ret = node->m_socket->sendBytes(str, length);
                delete [] str;
            }

            readable.push_back(node->m_socket);
        }

        if (Net::Socket::select(readable, writeable, exceptable, 50000))
        {
            Net::Socket::SocketList::iterator it = readable.begin();
            for (; it != readable.end(); it++)
            {
                Net::Socket* s = *it;
                char buffer[1000];
                memset(buffer, 0, sizeof(buffer));

                int len = s->receiveBytes(buffer, 1000);

                SocketNode* node = searchSocketNode(s);
                node->m_read.push(buffer, len);

                node->m_handler->getWorkThread()->postTask(Bind(&SocketHandler::readReady, node->m_handler, s));
            }
        }
    }
}

bool IOManager::addSocket(Net::Socket *socket, SocketHandler *handler)
{
    addSocketNode(socket, handler);
}

int IOManager::readSocket(Net::Socket *socket, char* s, int length)
{
    int readLen = 0;
    SocketNode* node = searchSocketNode(socket);

    char* tmp = node->m_read.pop(&readLen);

    memcpy(s, tmp, readLen);
    return readLen;
}

int IOManager::writeSocket(Net::Socket *socket, const char* s, int length)
{
    SocketNode* node = searchSocketNode(socket);

    node->m_write.push(s, length);

    return length;
}


void IOManager::addSocketNode(Net::Socket *socket, SocketHandler *handler)
{
    SocketNode* node = new SocketNode(socket, handler);
    m_sockets.push_back(node);
}

void IOManager::deleteSocketNode(Net::Socket *socket)
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

IOManager::SocketNode* IOManager::searchSocketNode(Net::Socket *socket)
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
