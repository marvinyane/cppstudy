#include "Socket.h"
#include "SocketAddress.h"
#include "IPAddress.h"
#include "NetworkInterface.h"

#include "Poco/Net/Socket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Exception.h"

#include <iostream>

namespace base{
namespace Net{

Socket::Socket()
{
}

Socket::~Socket()
{
}

int Socket::sendBytes(const char* buffer, int length){return 0;}
int Socket::receiveBytes(char* buffer, int length){return 0;}
StreamSocket* Socket::acceptConnection(){return NULL;}

void Socket::setBlocking(bool s){}

int Socket::select(SocketList& readList, SocketList& writeList,SocketList& exceptList, const int timeout)
{
    int ret = 0;

    Poco::Net::Socket::SocketList m_readList;
    Poco::Net::Socket::SocketList m_writeList;
    Poco::Net::Socket::SocketList m_exceptList;

    SocketList::iterator it = readList.begin();
    for (; it != readList.end(); ++it)
    {
        m_readList.push_back(*((*it)->getProxy()));
    }

    it = writeList.begin();
    for (; it != writeList.end(); ++it)
    {
        m_writeList.push_back(*((*it)->getProxy()));
    }

    it = exceptList.begin();
    for (; it != exceptList.end(); ++it)
    {
        m_exceptList.push_back(*((*it)->getProxy()));
    }

    try 
    {
        ret = Poco::Net::Socket::select(m_readList, m_writeList, m_exceptList, Poco::Timespan(timeout));
        
        it = readList.begin();
        while (it != readList.end())
        {
            if (std::find(m_readList.begin(), m_readList.end(), *((*it)->getProxy())) == m_readList.end())
            {
                it = readList.erase(it);
            }
            else
            {
                it ++;
            }
        }

        it = writeList.begin();
        while( it != writeList.end())
        {
            if (std::find(m_writeList.begin(), m_writeList.end(), *((*it)->getProxy())) == m_writeList.end())
            {
                it = writeList.erase(it);
            }
            else
            {
                it ++;
            }
        }

        it = exceptList.begin();
        while( it != exceptList.end())
        {
            if (std::find(m_exceptList.begin(), m_exceptList.end(), *((*it)->getProxy())) == m_exceptList.end())
            {
                it = exceptList.erase(it);
            }
            else
            {
                it ++;
            }
        }

    }

    catch(Poco::Exception& e)
    {
        std::cout << "select poco exception : " << e.what() << "\n";
    }
    catch(...)
    {
        std::cout << "other exception? \n";
    }


    return ret;
}


StreamSocket::StreamSocket()
{
    proxy = new Poco::Net::StreamSocket;
}


StreamSocket::StreamSocket(Poco::Net::StreamSocket* socket)
{
    proxy = new Poco::Net::StreamSocket(*socket);
}

StreamSocket::~StreamSocket()
{
    delete proxy;
}

int StreamSocket::connect(const SocketAddress& address)
{
    try
    {
        proxy->connect(address.getProxy());
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}

int StreamSocket::connect(const SocketAddress& address, const int timeout)
{
    try
    {
        proxy->connect(address.getProxy(), Poco::Timespan(timeout));
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}
            
int StreamSocket::connectNB(const SocketAddress& address)
{
    try
    {
        proxy->connectNB(address.getProxy());
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}

void StreamSocket::close()
{
    proxy->close();
}


void StreamSocket::shutdown()
{
    proxy->shutdown();
}

Poco::Net::Socket* StreamSocket::getProxy()
{
    return proxy;
}

SocketAddress StreamSocket::getAddress()
{
    Poco::Net::SocketAddress addr = proxy->address();
    return SocketAddress(addr);
}

void StreamSocket::setBlocking(bool s)
{
    proxy->setBlocking(s);
}

int StreamSocket::sendBytes(const char* buffer, int length)
{
    int ret = 0;
    try
    {
        ret = proxy->sendBytes(reinterpret_cast<const void*>(buffer), length);
    }
    catch (Poco::Exception& e)
    {
        std::cout << "send bytes exception : " << e.what() << "\n";
    }

    return ret;
}

int StreamSocket::receiveBytes(char* buffer, int length)
{
    int ret = 0;

    try
    {
        ret = proxy->receiveBytes(reinterpret_cast<void*>(buffer), length);
    }
    catch(Poco::TimeoutException& e)
    {
        std::cout << "time out : " << e.what() << "\n";
    }
    catch(Poco::Net::NetException& e)
    {
        std::cout << "Net : " << e.what() << "\n";
    }
    catch(...)
    {
    }

    return ret;
}



ServerSocket::ServerSocket()
{
    proxy = new Poco::Net::ServerSocket;
}

ServerSocket::~ServerSocket()
{
    delete proxy;
}

void ServerSocket::close()
{
    proxy->close();
}

SocketAddress ServerSocket::getAddress()
{
    return SocketAddress(proxy->address());
}

Poco::Net::Socket* ServerSocket::getProxy()
{
    return proxy;
}

void ServerSocket::bind(SocketAddress &addr, bool reuse)
{
    proxy->bind(addr.getProxy(), reuse);
}

void ServerSocket::bind(UInt16 port)
{
    proxy->bind(port);
}

void ServerSocket::listen()
{
    proxy->listen();
}

StreamSocket* ServerSocket::acceptConnection()
{
    StreamSocket* socket = NULL;
    try
    {
        Poco::Net::StreamSocket s = proxy->acceptConnection();
        socket = new StreamSocket(&s);
    }
    catch(Poco::IOException& e)
    {
        std::cout << "exception? : " << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "unknown exception?\n";
    }

    return socket;
}

void ServerSocket::setBlocking(bool s)
{
    proxy->setBlocking(s);
}



MulticastSocket::MulticastSocket():
    proxy(new Poco::Net::MulticastSocket)
{
}

MulticastSocket::MulticastSocket(const MulticastSocket& other)
{
    proxy = other.proxy;
}

MulticastSocket::MulticastSocket(const Poco::Net::MulticastSocket& other):
    proxy (new Poco::Net::MulticastSocket(other))
{
}

MulticastSocket::~MulticastSocket()
{
}

MulticastSocket& MulticastSocket::operator=(const MulticastSocket& other)
{
    proxy = other.proxy;
    return *this;
}

void MulticastSocket::close()
{
    proxy->close();
}

void MulticastSocket::bind(SocketAddress& addr, bool reuse)
{
    proxy->bind(addr.getProxy(), reuse);
}

Poco::Net::Socket* MulticastSocket::getProxy()
{
    return proxy.get();
}

SocketAddress MulticastSocket::getAddress()
{
    Poco::Net::SocketAddress addr = proxy->address();
    return SocketAddress(addr);
}

void MulticastSocket::setBlocking(bool flag)
{
    proxy->setBlocking(flag);
}


void MulticastSocket::setInterface(const NetworkInterface& interfc)
{
    proxy->setInterface(interfc.getProxy());
}

void MulticastSocket::setLoopback(bool flag)
{
    proxy->setLoopback(flag);
}

void MulticastSocket::joinGroup(const IPAddress& groupAddress, const NetworkInterface& interfc)
{
    proxy->joinGroup(groupAddress.getProxy(), interfc.getProxy());
}

int MulticastSocket::sendBytes(const char* buffer, int length)
{
    std::cout << "proxy address : " << proxy->address().toString() << "\n";
    proxy->sendTo(buffer, length,  proxy->address());
}

int MulticastSocket::receiveBytes(char* buffer, int length)
{
    std::cout << "data coming.... \n";
    return proxy->receiveBytes(buffer, length);
}

}  // NET
} // base
