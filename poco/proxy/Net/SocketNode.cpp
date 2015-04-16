#include "IOManager.h"
#include "Socket.h"

namespace base
{
    SocketNode::SocketNode(std::tr1::shared_ptr<Net::Socket> socket):
        m_socket(socket)
    {
    }

    SocketNode::SocketNode(const SocketNode& other)
    {
        m_socket = other.m_socket;
    }

    SocketNode::~SocketNode()
    {
    }

    SocketNode& SocketNode::operator=(const base::SocketNode &other)
    {
        m_socket = other.m_socket;
        return *this;
    }

    int SocketNode::read(char *buffer, int length)
    {
        // call m_socket read
        return m_socket->read(buffer, length);
    }

    int SocketNode::write(const char *buffer, int length)
    {
        return m_socket->write(buffer, length);
    }

    int SocketNode::readAvalible()
    {
    }

    void SocketNode::close()
    {
        m_socket->close();
    }

    Net::Socket* SocketNode::getSocket()
    {
        return m_socket.get();
    }
}
