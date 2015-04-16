#include "Socket.h"
#include "SocketAddress.h"
#include "IPAddress.h"
#include "NetworkInterface.h"
#include "RingBuffer.h"

#include "Poco/Net/Socket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Exception.h"

#include <iostream>

namespace base{
namespace Net{

Socket::Socket(base::SocketHandler* handler) : 
    m_handler(handler), 
    m_read(),
    m_write(),
    m_readLeft(NULL),
    m_readSign(0),
    m_readLen(0),
    m_writeLeft(NULL),
    m_writeSign(0),
    m_writeLen(0)
{
}

Socket::~Socket()
{
}

int Socket::read(char* s, int length)
{
    int readSign = 0;
    if (m_readLeft)
    {
        if ((m_readLen - m_readSign) > length)
        {
            memcpy(s, m_readLeft + m_readSign, length);
            m_readLen -= length;
            m_readSign += length;

            return length;
        }
        else
        {
            memcpy(s, m_readLeft + m_readSign, m_readLen - m_readSign);
            readSign += m_readLen - m_readSign;

            m_readLeft = NULL;
            m_readLen = 0;
            m_readSign = 0;
        }
    }

    while (1)
    {
        int readLen = 0;
        char* tmp = m_read.pop(&readLen);
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

            m_readLeft = tmp;
            m_readSign = length - readSign;
            m_readLen = readLen;

            return length;
        }
    }

}

int Socket::write(const char* buffer, int length)
{
    m_write.push(buffer, length);
}

char* Socket::readToSend(int& length)
{
    if (m_writeLeft)
    {
        char* ret = m_writeLeft + m_writeSign;
        length = m_writeLen - m_writeSign;

        m_writeLeft = NULL;
        m_writeSign = 0;
        m_writeLen = 0;

        return ret;
    }

    if (m_write.size() > 0)
    {
        char* str = m_write.pop(&length);
        if (str == NULL)
        {
            length = 0;
        }

        return str;
    }

    length = 0;
    return NULL;
}

void Socket::SendFailed(char* buffer, int length, int sign)
{
    m_writeLeft = buffer;
    m_writeSign = sign;
    m_writeLen = length;
}

int Socket::writeFromRead(const char* buffer, int length)
{
    m_read.push(buffer, length);
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

}  // NET
} // base
