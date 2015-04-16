#include "IOManager.h"
#include "WorkThread.h"

#include "NetworkInterface.h"
#include "Socket.h"

#include <iostream>
#include <cstring>

bool running = true;

// TODO
class MyHandler : public base::SocketHandler
{
    public:
        MyHandler() :
            m_io(new base::IOManager),
            m_socket(NULL)
        {
            m_work = new base::WorkThread;
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

            //this->disconnect();
        }
        virtual void disconnected(base::Net::Socket* socket)
        {
            /*disconnect!*/
            std::cout << "disconnected!\n";
            delete m_socket;
            m_socket = NULL;

            running = false;
        }


        void initMulticast()
        {
            base::Net::NetworkInterface::NetworkInterfaceList list = base::Net::NetworkInterface::list();
            base::Net::NetworkInterface::NetworkInterfaceList::iterator it = list.begin();

            for (; it != list.end(); it++)
            {
                std::cout << "interface name : " << (*it).name() << ", index:" << (*it).index() << "\n";
            }
            
            base::Net::NetworkInterface interface = base::Net::NetworkInterface::forIndex(5);

            m_multi = new base::Net::MulticastSocket;

            m_multi->setInterface(interface);
            base::Net::SocketAddress addr("239.255.255.250:1900");
            m_multi->bind(addr, true);
            m_multi->joinGroup(base::Net::IPAddress("239.255.255.250"), interface);
            m_multi->setLoopback(false);

            m_search = new base::Net::MulticastSocket;
            m_search->setInterface(interface);
            base::Net::SocketAddress addr_search(interface.address(), 1900);
            std::cout << "interface address : " << addr_search.toString() << "\n";
            m_search->bind(addr_search, true);
            m_search->setLoopback(false);


            std::string query = "M-SEARCH * HTTP/1.1\r\nHOST: 239.250.250.250:1900\r\n\
                         MAN: \"ssdp:discover\"\r\nMX: 1\r\n\
                         ST: urn:schemas-upnp-org:device:TmServerDevice:1\r\n\r\n";

            m_io->addSocket(m_multi, this);
            m_io->addSocket(m_search, this);

            m_search->sendBytes(query.c_str(), query.size());
        }

        virtual base::WorkThread* getWorkThread()
        {
            return m_work;
        }

    private:
        base::WorkThread* m_work;
        base::IOManager* m_io;
        base::Net::StreamSocket* m_socket;
        base::Net::MulticastSocket *m_multi;
        base::Net::MulticastSocket *m_search;
        
};

int main()
{
    MyHandler handler;
    handler.initMulticast();
    //

    //base::Net::NetworkInterface::NetworkInterfaceList list = base::Net::NetworkInterface::list();
    //base::Net::NetworkInterface::NetworkInterfaceList::iterator it = list.begin();

    //for (; it != list.end(); ++it)
    //{
        //std::cout << "name : " << (*it).name() << "\n";
    //}
    //
    //base::Net::SocketAddress s0;
    //base::Net::SocketAddress s1("121.0.0.1:6666");

    //s0 = s1;

    //base::Net::SocketAddress s2(s0);

    //std::cout << s1.toString() << s2.toString() << s0.toString() << "\n";
    //
    



    while (running)
    {
        sleep (1);
    }

    return 0;
}
