#include "SocketAddress.h"
#include "IPAddress.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/IPAddress.h"

namespace base{
namespace Net{

SocketAddress::SocketAddress()
{
    proxy = new Poco::Net::SocketAddress;
}

SocketAddress::SocketAddress(const IPAddress& hostAddress, base::UInt16 portNumber)
{
    //proxy = new Poco::Net::SocketAddress(*hostAddress.proxy, portNumber);
}

SocketAddress::SocketAddress(base::UInt16 port)
{
    proxy = new Poco::Net::SocketAddress(port);
}

SocketAddress::SocketAddress(const std::string& hostAddress, base::UInt16 portNumber)
{
    proxy = new Poco::Net::SocketAddress(hostAddress, portNumber);
}

SocketAddress::SocketAddress(const std::string& hostAddress, const std::string& portNumber)
{
    proxy = new Poco::Net::SocketAddress(hostAddress, portNumber);
}

SocketAddress::SocketAddress(const std::string& hostAndPort)
{
    try
    {
        proxy = new Poco::Net::SocketAddress(hostAndPort);
    }
    catch(...)
    {
        proxy = new Poco::Net::SocketAddress("8.8.8.8:8080");
    }
}

SocketAddress::SocketAddress(const SocketAddress& addr)
{
    proxy = new Poco::Net::SocketAddress(*addr.proxy);
}

//SocketAddress::SocketAddress(const struct sockaddr* addr, base_socklen_t length)
//{
    //proxy = new Poco::Net::SocketAddress(addr, length);
//}

SocketAddress::~SocketAddress()
{
    delete proxy;
}

SocketAddress& SocketAddress::operator = (const SocketAddress& socketAddress)
{
    proxy->operator=(*socketAddress.proxy);
    return *this;
}

IPAddress SocketAddress::host() const
{
    Poco::Net::IPAddress addr = proxy->host();
    return IPAddress(addr);
}

base::UInt16 SocketAddress::port() const
{
    return proxy->port();
}

base_socklen_t SocketAddress::length() const
{
    return 0;
}

const struct sockaddr* SocketAddress::addr() const
{
    return NULL;
}

int SocketAddress::af() const
{
    return proxy->af();
}

std::string SocketAddress::toString() const
{
    return proxy->toString();
}

IPAddress::Family SocketAddress::family() const
{
    return IPAddress::IPv4;
}

bool SocketAddress::operator < (const SocketAddress& socketAddress) const
{
    return proxy->operator<(*(socketAddress.proxy));
}
bool SocketAddress::operator == (const SocketAddress& socketAddress) const
{
    return proxy->operator==(*(socketAddress.proxy));
}
bool SocketAddress::operator != (const SocketAddress& socketAddress) const
{
    return proxy->operator!=(*(socketAddress.proxy));
}

}}
