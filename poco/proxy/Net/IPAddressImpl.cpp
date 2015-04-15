#include "IPAddress.h"

#include "Poco/Net/IPAddress.h"

namespace base{
namespace Net{

static Poco::Net::IPAddress::Family convert2PocoFamily(IPAddress::Family family)
{
    Poco::Net::IPAddress::Family f;
    if (family == IPAddress::IPv4)
    {
        f = Poco::Net::IPAddress::IPv4;
    }
    else
    {
        f = Poco::Net::IPAddress::IPv6;
    }

    return f;
}

static IPAddress::Family convert2BaseFamily(Poco::Net::IPAddress::Family family)
{
    IPAddress::Family f;
    if (family == Poco::Net::IPAddress::IPv4)
    {
        f = IPAddress::IPv4;
    }
    else
    {
        f = IPAddress::IPv6;
    }

    return f;
}

IPAddress::IPAddress()
{
    proxy = new Poco::Net::IPAddress;
}

IPAddress::IPAddress(const IPAddress& addr)
{
    proxy = new Poco::Net::IPAddress(*addr.proxy);
}

IPAddress::IPAddress(Family family)
{
    proxy = new Poco::Net::IPAddress(convert2PocoFamily(family));
}

IPAddress::IPAddress(const std::string& addr)
{
    try
    {
        proxy = new Poco::Net::IPAddress(addr);
    }
    catch(...)
    {
        proxy = new Poco::Net::IPAddress(Poco::Net::IPAddress::IPv4);
    }
}

IPAddress::IPAddress(const std::string& addr, Family family)
{
    proxy = new Poco::Net::IPAddress(addr, convert2PocoFamily(family));
}

IPAddress::IPAddress(const void* addr, base_socklen_t length)
{
    proxy = new Poco::Net::IPAddress(addr, length);
}

IPAddress::IPAddress(const void* addr, base_socklen_t length, base::UInt32 scope)
{
    proxy = new Poco::Net::IPAddress(addr, length, scope);
}

IPAddress::IPAddress(unsigned prefix, Family family)
{
    proxy = new Poco::Net::IPAddress(prefix, convert2PocoFamily(family));
}

//IPAddress::IPAddress(const struct sockaddr& sockaddr)
//{
//}
//
IPAddress::IPAddress(const Poco::Net::IPAddress& address)
{
    proxy = new Poco::Net::IPAddress(address);
}


IPAddress::~IPAddress()
{
    delete proxy;
}

IPAddress& IPAddress::operator = (const IPAddress& addr)
{
    proxy->operator=(*addr.proxy);
    return *this;
}

IPAddress::Family IPAddress::family() const
{
    return convert2BaseFamily(proxy->family());
}

base::UInt32 IPAddress::scope() const
{
    return proxy->scope();
}

std::string IPAddress::toString() const
{
    return proxy->toString();
}

bool IPAddress::isWildcard() const
{
    return proxy->isWildcard();
}

bool IPAddress::isBroadcast() const
{
    return proxy->isBroadcast();
}

bool IPAddress::isLoopback() const
{
    return proxy->isLoopback();
}

bool IPAddress::isMulticast() const
{
    return proxy->isMulticast();
}

bool IPAddress::isUnicast() const
{
    return proxy->isUnicast();
}

bool IPAddress::isLinkLocal() const
{
    return proxy->isLinkLocal();
}

bool IPAddress::isSiteLocal() const
{
    return proxy->isSiteLocal();
}

bool IPAddress::isIPv4Compatible() const
{
    return proxy->isIPv4Compatible();
}

bool IPAddress::isIPv4Mapped() const
{
    return proxy->isIPv4Mapped();
}

bool IPAddress::isWellKnownMC() const
{
    return proxy->isWellKnownMC();
}

bool IPAddress::isNodeLocalMC() const
{
    return proxy->isNodeLocalMC();
}

bool IPAddress::isLinkLocalMC() const
{
    return proxy->isLinkLocalMC();
}

bool IPAddress::isSiteLocalMC() const
{
    return proxy->isSiteLocalMC();
}

bool IPAddress::isOrgLocalMC() const
{
    return proxy->isOrgLocalMC();
}

bool IPAddress::isGlobalMC() const
{
    return proxy->isGlobalMC();
}

bool IPAddress::operator == (const IPAddress& addr) const
{
    return proxy->operator==(*addr.proxy);
}	
bool IPAddress::operator != (const IPAddress& addr) const
{
    return proxy->operator!=(*addr.proxy);
}
bool IPAddress::operator <  (const IPAddress& addr) const
{
    return proxy->operator<(*addr.proxy);
}
bool IPAddress::operator <= (const IPAddress& addr) const
{
    return proxy->operator<=(*addr.proxy);
}
bool IPAddress::operator >  (const IPAddress& addr) const
{
    return proxy->operator>(*addr.proxy);
}
bool IPAddress::operator >= (const IPAddress& addr) const
{
    return proxy->operator>=(*addr.proxy);
}
IPAddress IPAddress::operator & (const IPAddress& addr) const
{
    Poco::Net::IPAddress t = proxy->operator&(*addr.proxy);
    return IPAddress(t);
}
IPAddress IPAddress::operator | (const IPAddress& addr) const
{
    Poco::Net::IPAddress t = proxy->operator|(*addr.proxy);
    return IPAddress(t);
}
IPAddress IPAddress::operator ^ (const IPAddress& addr) const
{
    Poco::Net::IPAddress t = proxy->operator^(*addr.proxy);
    return IPAddress(t);
}
IPAddress IPAddress::operator ~ () const
{
    Poco::Net::IPAddress t = proxy->operator~();
    return IPAddress(t);
}

base_socklen_t IPAddress::length() const
{
    return proxy->length();
}

const void* IPAddress::addr() const
{
    return proxy->addr();
}

int IPAddress::af() const
{
    return proxy->af();
}

unsigned IPAddress::prefixLength() const
{
    return proxy->prefixLength();
}

void IPAddress::mask(const IPAddress& mask)
{
    proxy->mask(*mask.proxy);
}

void IPAddress::mask(const IPAddress& mask, const IPAddress& set)
{
    proxy->mask(*mask.proxy, *set.proxy);
}

IPAddress IPAddress::parse(const std::string& addr)
{
    return IPAddress(addr);
}

bool IPAddress::tryParse(const std::string& addr, IPAddress& result)
{
    //TODO:
    return false;
}

IPAddress IPAddress::wildcard(Family family)
{
    return IPAddress(family);
}

#if 0
IPAddress IPAddress::broadcast()
{
}
#endif

}}
