#include "IOManager.h"
#include "WorkThread.h"

#include "NetworkInterface.h"

#include <iostream>
#include <cstring>

bool running = true;

// TODO
class MyHandler : public base::SocketHandler
{
    public:
        MyHandler() : 
            SocketHandler(new base::WorkThread),
            m_io(new base::IOManager),
            m_socket(NULL)
        {
            m_work->start();
        }
        ~MyHandler()
        {
            /*close socket?*/
            
            delete m_io;
            delete m_work;

        }

        int connect()
        {
            base::Net::SocketAddress addr("localhost", 6666);
            m_socket = new base::Net::StreamSocket; 

            if (m_socket->connect(addr) != 0)
            {
                return -1;
            }

            m_io->addSocket(m_socket, this);
            return 0;
        }

        int disconnect()
        {
            if (m_socket)
            {
                m_io->removeSocket(m_socket);
                m_socket->close();
                return 0;
            }

            return -1;
        }

        void sayHello()
        {
            m_socket->sendBytes("hello", 6);
        }

        void waitHello()
        {
            m_io->addServerSocket(6668, this);
        }

        virtual void connected(base::Net::StreamSocket* socket)
        {
            std::cout << "connected with : " << socket->getAddress().toString() << "\n";
            m_socket = socket;
        }
        virtual void readReady(base::Net::Socket* socket)
        {
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));

            int len = m_io->readSocket(socket, buffer, 999);
            std::cout << "recv size is : " << len << std::endl;
            std::cout << buffer << "\n";

            this->disconnect();
        }
        virtual void disconnected(base::Net::Socket* socket)
        {
            /*disconnect!*/
            std::cout << "disconnected!\n";
            delete m_socket;
            m_socket = NULL;

            running = false;
        }

    private:
        base::IOManager* m_io;
        base::Net::StreamSocket* m_socket;
        
};

int main()
{
    //MyHandler handler;
    //handler.waitHello();
    //

    base::Net::NetworkInterface::NetworkInterfaceList list = base::Net::NetworkInterface::list();
    base::Net::NetworkInterface::NetworkInterfaceList::iterator it = list.begin();

    for (; it != list.end(); ++it)
    {
        std::cout << "name : " << (*it).name() << "\n";
    }

    while (running)
    {
        sleep (1);
    }

    return 0;
}
