#include "Socket.h"
#include "SocketAddress.h"

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

namespace base{
namespace Net{

StreamSocket::StreamSocket(SocketHandler* handler):
    Socket(handler),
    proxy(new Poco::Net::StreamSocket)
{
}
StreamSocket::StreamSocket(const StreamSocket& other):
    Socket(other.m_handler)
{
    proxy = other.proxy;
}
StreamSocket::~StreamSocket()
{
}

StreamSocket& StreamSocket::operator=(const StreamSocket & other)
{
    proxy = other.proxy;
}

StreamSocket::StreamSocket(Poco::Net::StreamSocket& socket, SocketHandler* handler):
    Socket(handler),
    proxy(new Poco::Net::StreamSocket(socket))
{
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
    return proxy.get();
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

void StreamSocket::readEvent()
{
    // ready read event
}

void StreamSocket::writeEvent()
{

}

void StreamSocket::exceptEvent()
{

}



}} //namespace
