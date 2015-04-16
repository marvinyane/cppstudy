#include <iostream>

#include "Socket.h"
#include "IPAddress.h"
#include "SocketAddress.h"

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"

namespace base{
namespace Net{

ServerSocket::ServerSocket(SocketHandler* handler):
    Socket(handler),
    proxy(new Poco::Net::ServerSocket)
{
}

ServerSocket::ServerSocket(const ServerSocket& other):
    Socket(other.m_handler)
{
    proxy = other.proxy;
}

ServerSocket::~ServerSocket()
{
}

ServerSocket& ServerSocket::operator=(const ServerSocket& other)
{
    proxy = other.proxy;
    return *this;
}

SocketAddress ServerSocket::getAddress()
{
    return SocketAddress(proxy->address());
}

Poco::Net::Socket* ServerSocket::getProxy()
{
    return proxy.get();
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

void ServerSocket::close()
{
    proxy->close();
}

std::tr1::shared_ptr<StreamSocket> ServerSocket::acceptConnection()
{
    std::tr1::shared_ptr<StreamSocket> socket;
    try
    {
        Poco::Net::StreamSocket s = proxy->acceptConnection();
        socket = std::tr1::shared_ptr<StreamSocket>(new StreamSocket(s, m_handler));
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

void ServerSocket::setBlocking(bool flag)
{
    proxy->setBlocking(flag);
}

void ServerSocket::readEvent()
{
    // ready read event
}

void ServerSocket::writeEvent()
{

}

void ServerSocket::exceptEvent()
{

}









}} // namespace
