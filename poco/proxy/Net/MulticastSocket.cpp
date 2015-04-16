#include "Socket.h"
#include "SocketAddress.h"
#include "NetworkInterface.h"

#include "Poco/Net/MulticastSocket.h"


namespace base{
namespace Net{

MulticastSocket::MulticastSocket(SocketHandler* handler):
    Socket(handler),
    proxy(new Poco::Net::MulticastSocket)
{
}

MulticastSocket::MulticastSocket(const MulticastSocket& other):
    Socket(other.m_handler)
{
    proxy = other.proxy;
}

MulticastSocket::MulticastSocket(const Poco::Net::MulticastSocket& other, SocketHandler* handler):
    Socket(handler),
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


void MulticastSocket::readEvent()
{
    // ready read event
}

void MulticastSocket::writeEvent()
{

}

void MulticastSocket::exceptEvent()
{

}


}} // namespace
