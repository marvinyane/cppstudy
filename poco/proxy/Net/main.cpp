#include "IOManager.h"
#include "../Foundation/WorkThread.h"

#include <iostream>

#include "Poco/Net/StreamSocket.h"


class MyHandler : public base::SocketHandler
{
    public:
        MyHandler(base::WorkThread* work, base::IOManager* manager) : 
            SocketHandler(work),
            m_io(manager)
        {
        }
        void readReady(Poco::Net::Socket& socket)
        {
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));
            int len = m_io->readSocket(socket, buffer, sizeof(buffer));

            std::cout << buffer << " size is : " << len << std::endl;
        }

    private:
        base::IOManager* m_io;
        
};

int main()
{
    base::IOManager m;
    base::WorkThread w;

    MyHandler *handler = new MyHandler(&w, &m);

    Poco::Net::SocketAddress addr("localhost:6666");

    Poco::Net::StreamSocket socket(addr);

    m.addSocket(socket, handler);

    while (1)
    {
        char* s = new char[20];
        memcpy(s, "hello world", 12);
        m.writeSocket(socket, s, 12);
        sleep (1);
    }
    return 0;
}
