#include "Socket.h"
#include "SocketAddress.h"

#include "Poco/Net/Socket.h"
#include "Poco/Net/SocketStream.h"
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

int Socket::select(SocketList& readList, SocketList& writeList,SocketList& exceptList, const int timeout)
{
    int ret = 0;

    Poco::Net::Socket::SocketList m_readList;
    Poco::Net::Socket::SocketList m_writeList;
    Poco::Net::Socket::SocketList m_exceptList;

    SocketList::iterator it = readList.begin();
    for (; it != readList.end(); ++it)
    {
        m_readList.push_back(*((*it)->getPorxy()));
    }

    it = writeList.begin();
    for (; it != writeList.end(); ++it)
    {
        m_writeList.push_back(*((*it)->getPorxy()));
    }

    it = exceptList.begin();
    for (; it != exceptList.end(); ++it)
    {
        m_exceptList.push_back(*((*it)->getPorxy()));
    }

    try 
    {
        ret = Poco::Net::Socket::select(m_readList, m_writeList, m_exceptList, Poco::Timespan(timeout));
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

StreamSocket::~StreamSocket()
{
    delete proxy;
}

int StreamSocket::connect(const SocketAddress& address)
{
    try
    {
        proxy->connect(Poco::Net::SocketAddress(address.toString()));
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
        proxy->connect(Poco::Net::SocketAddress(address.toString()), Poco::Timespan(timeout));
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
        proxy->connectNB(Poco::Net::SocketAddress(address.toString()));
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

Poco::Net::Socket* StreamSocket::getPorxy()
{
    return proxy;
}

int StreamSocket::sendBytes(const char* buffer, int length)
{
    std::cout << "send bytes fd : " << proxy->impl()->sockfd() << "\n";
    return proxy->sendBytes(reinterpret_cast<const void*>(buffer), length);
}

int StreamSocket::receiveBytes(char* buffer, int length)
{
    proxy->receiveBytes(reinterpret_cast<void*>(buffer), length);
}

}  // NET
} // base
