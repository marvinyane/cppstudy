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
            while (node->m_write.size() > 0)
            {
                int length = 0;
                char* str = node->m_write.pop(&length);
                // TODO:
                node->m_socket->sendBytes(str, length);
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

                int len = s->receiveBytes(buffer, sizeof(buffer));

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
    return true;
}

bool IOManager::removeSocket(Net::Socket* socket)
{
    return deleteSocketNode(socket);
}

int IOManager::readSocket(Net::Socket *socket, char* s, int length)
{
    int readSign = 0;
    SocketNode* node = searchSocketNode(socket);

    if (node->m_readLeft)
    {
        if ((node->m_readLen - node->m_readSign) > length)
        {
            memcpy(s, node->m_readLeft + node->m_readSign, length);
            node->m_readLen -= length;
            node->m_readSign += length;
     
            return length;
        }
        else
        {
            memcpy(s, node->m_readLeft + node->m_readSign, node->m_readLen - node->m_readSign);
            readSign += node->m_readLen - node->m_readSign;
            delete [] node->m_readLeft;
            node->m_readLeft = NULL;
            node->m_readSign = 0;
            node->m_readLen = 0;
        }
    }

    while (1)
    {
        int readLen = 0;
        char* tmp = node->m_read.pop(&readLen);
        if (tmp == NULL)
        {
            return readSign;
        }

        if (readLen <= (length - readSign))
        {
            memcpy(s + readSign, tmp, readLen);
            readSign += readLen;
            delete [] tmp;
        }
        else
        {
            if (readSign != length)
            {
                memcpy(s + readSign, tmp, length - readSign);
            }

            node->m_readLeft = tmp;
            node->m_readSign = length - readSign;
            node->m_readLen = readLen;

            return length;
        }
    }

    return 0;
}

int IOManager::writeSocket(Net::Socket *socket, const char* s, int length)
{
    SocketNode* node = searchSocketNode(socket);

    node->m_write.push(s, length);

    return length;
}

int IOManager::readSocketAvalible(Net::Socket *socket)
{
    SocketNode* node = searchSocketNode(socket);
    
    if (node)
    {
        return node->m_read.size() + node->m_readLen - node->m_readSign;
    }

    return 0;
}

void IOManager::addSocketNode(Net::Socket *socket, SocketHandler *handler)
{
    SocketNode* node = new SocketNode(socket, handler);
    m_sockets.push_back(node);
}

bool IOManager::deleteSocketNode(Net::Socket *socket)
{
    std::vector<SocketNode*>::iterator it = m_sockets.begin();

    for (; it != m_sockets.end(); it++)
    {
        if ((*it)->m_socket == socket)
        {
            m_sockets.erase(it);
            return true;
        }
    }

    return false;
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
