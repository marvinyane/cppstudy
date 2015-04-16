#include "NetworkInterface.h"
#include "Poco/Net/NetworkInterface.h"

#include "IPAddress.h"

namespace base{
namespace Net{

NetworkInterface::NetworkInterface():
    proxy(new Poco::Net::NetworkInterface)
{
}

NetworkInterface::NetworkInterface(const NetworkInterface& other)
{
    proxy = other.proxy;
}

NetworkInterface::NetworkInterface(Poco::Net::NetworkInterface& other):
    proxy(new Poco::Net::NetworkInterface(other))
{
}

NetworkInterface::~NetworkInterface()
{
}

NetworkInterface& NetworkInterface::operator=(const NetworkInterface& other)
{
    proxy = other.proxy;
    return *this;
}

NetworkInterface NetworkInterface::forIndex(int index)
{
    Poco::Net::NetworkInterface inter = Poco::Net::NetworkInterface::forIndex(index);
    return NetworkInterface(inter);
}

NetworkInterface::NetworkInterfaceList NetworkInterface::list()
{
    NetworkInterfaceList list;

    Poco::Net::NetworkInterface::NetworkInterfaceList poco_list = Poco::Net::NetworkInterface::list();
    Poco::Net::NetworkInterface::NetworkInterfaceList::iterator it = poco_list.begin();

    for(; it != poco_list.end(); ++it)
    {
        list.push_back(NetworkInterface(*it));
    }

    return list;
}

const IPAddress& NetworkInterface::address()
{
    const Poco::Net::IPAddress& addr = proxy->address();
    this->addr = new IPAddress(addr);

    return *(this->addr);
}

const std::string& NetworkInterface::name()
{
    return proxy->name();
}


}}
