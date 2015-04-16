#include <iostream>
#include <cstring>
#include <algorithm>

#include "IOManager.h"
#include "Socket.h"

namespace base
{

IOManager::IOManager() : 
    m_running(true),
    m_thread(new WorkThread("IOThread")),
    m_sockets(),
    m_mutex()
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
        /**/
        Net::Socket::SocketList readable;
        Net::Socket::SocketList writeable;
        Net::Socket::SocketList exceptable;
        m_mutex.lock();
        std::vector<SocketNode*>::iterator it = m_sockets.begin();
        for (; it != m_sockets.end(); it++)
        {
            SocketNode* node = *it;
            if (node->stateToSelect())
            {
                SocketNode* node = *it;
                if (node->m_write.size() > 0)
                {
                    writeable.push_back(node->m_socket);
                }

                readable.push_back(node->m_socket);
                exceptable.push_back(node->m_socket);
            }
        }
        m_mutex.unlock();

        Net::Socket::select(readable, writeable, exceptable, 50000);
        {
            m_mutex.lock();
            it = m_sockets.begin();
            while (it != m_sockets.end())
            {
                SocketNode* node = *it;
                if (node->stateToClose())
                {
                    /*read this socket in all able*/
                    readable.erase(std::remove(readable.begin(), readable.end(), node->m_socket), 
                            readable.end());

                    writeable.erase(std::remove(writeable.begin(), writeable.end(), node->m_socket), 
                            writeable.end());

                    exceptable.erase(std::remove(exceptable.begin(), exceptable.end(), node->m_socket), 
                            exceptable.end());

                    node->m_handler->getWorkThread()->postTask(Bind(&SocketHandler::disconnected,
                            node->m_handler, node->m_socket));

                    it = m_sockets.erase(it);
                    delete *it;
                }
                else
                {
                    it++;
                }
            }
            m_mutex.unlock();

            Net::Socket::SocketList::iterator it = readable.begin();
            for (; it != readable.end(); it++)
            {
                Net::Socket* s = *it;
                SocketNode* node = searchSocketNode(s);

                if (node == NULL)
                {
                    continue;
                }

                if (node->m_state == IOManager::Connected)
                {
                    char buffer[1000];
                    memset(buffer, 0, sizeof(buffer));

                    int len = s->receiveBytes(buffer, sizeof(buffer));

                    if (len > 0)
                    {
                        node->m_read.push(buffer, len);
                        node->m_handler->getWorkThread()->postTask(Bind(&SocketHandler::readReady,
                                    node->m_handler, s));
                    }
                    else if (len == 0)
                    {
                        node->m_handler->getWorkThread()->postTask(Bind(&SocketHandler::disconnected,
                                    node->m_handler, s));

                        /*remove?*/
                        s->close();
                        m_mutex.lock();
                        m_sockets.erase(std::remove(m_sockets.begin(), m_sockets.end(), node), m_sockets.end());
                        m_mutex.unlock();
                    }
                }
                else // listen
                {
                    Net::StreamSocket* socket = s->acceptConnection();
                    std::cout << "handler : " << (void*)node->m_handler << "\n";
                    addSocketNode(socket, node->m_handler, Connected);
                    node->m_handler->getWorkThread()->postTask(Bind(&SocketHandler::connected,
                                node->m_handler, socket));
                }
            }

            it = writeable.begin();
            for (; it != writeable.end(); ++it)
            {
                int length = 0;
                int sentLen = 0;

                Net::Socket* s = *it;
                SocketNode* node = searchSocketNode(s);

                if (node == NULL)
                {
                    continue;
                }

                if (node->m_writeLeft)
                {
                    int leftLen = node->m_writeLen - node->m_writeSign;
                    sentLen = s->sendBytes(node->m_writeLeft + node->m_writeSign, leftLen);

                    if (sentLen != leftLen)
                    {
                        node->m_writeSign += sentLen;
                        continue;
                    }
                    else
                    {
                        node->clearWriteLeft();
                    }
                }

                while (node->m_write.size() > 0)
                {
                    char* str = node->m_write.pop(&length);
                    if (str == NULL)
                    {
                        break;
                    }

                    sentLen = s->sendBytes(str, length);
                    if (sentLen != length)
                    {
                        node->m_writeLeft = str;
                        node->m_writeSign = length - sentLen;
                        node->m_writeLen = length;
                        break;
                    }

                    delete [] str;
                }
            }


            it = exceptable.begin();
            for (; it != exceptable.end(); ++it)
            {
                SocketNode* node = searchSocketNode(*it);
                if (node)
                {
                    std::cout << "socket except!" << (void*)node << "\n";
                }
            }
        }
    }

    m_thread->postTask(Bind(&IOManager::run, this));
}

bool IOManager::addServerSocket(Net::SocketAddress& addr, SocketHandler *handler)
{
    Net::ServerSocket *socket = new Net::ServerSocket;
    socket->bind(addr, true);

    socket->listen();

    socket->setBlocking(false);

    addSocketNode(socket, handler, Listen);

    return true;
}

bool IOManager::addServerSocket(UInt16 port, SocketHandler *handler)
{
    Net::ServerSocket *socket = new Net::ServerSocket;
    socket->bind(port);

    socket->listen();
    
    socket->setBlocking(false);

    addSocketNode(socket, handler, Listen);

    return true;
}

bool IOManager::addSocket(Net::Socket *socket, SocketHandler *handler)
{
    addSocketNode(socket, handler, Connected);

    return true;
}

bool IOManager::removeSocket(Net::Socket* socket)
{
    SocketNode* node = searchSocketNode(socket);
    if (node == NULL)
    {
        return false;
    }

    std::cout << "set closing \n";
    node->m_state = Closing;
    return true;
}

int IOManager::readSocket(Net::Socket *socket, char* s, int length)
{
    int readSign = 0;
    SocketNode* node = searchSocketNode(socket);

    if (node == NULL)
    {
        return 0;
    }

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

            node->clearReadLeft();
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

    if (node)
    {
        node->m_write.push(s, length);
        return length;
    }
    return 0;
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

void IOManager::addSocketNode(Net::Socket *socket, SocketHandler *handler, IOManager::State s)
{
    SocketNode* node = new SocketNode(socket, handler, s);
    m_mutex.lock();
    m_sockets.push_back(node);
    m_mutex.unlock();
}

IOManager::SocketNode* IOManager::searchSocketNode(Net::Socket *socket)
{
    m_mutex.lock();
    std::vector<SocketNode*>::iterator it = m_sockets.begin();

    for (; it != m_sockets.end(); it++)
    {
        if ((*it)->m_socket == socket)
        {
            m_mutex.unlock();
            return *it;
        }
    }
    m_mutex.unlock();

    return NULL;
}

} //namespace
