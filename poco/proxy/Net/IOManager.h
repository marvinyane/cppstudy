#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

#include "../Foundation/RingBuffer.h"
#include "../Foundation/WorkThread.h"

#include "Socket.h"
#include "SocketAddress.h"

#include <string>

namespace base
{

class WorkThread;

class SocketHandler
{
    public:
        SocketHandler(){}
        SocketHandler(base::WorkThread *work) : m_work(work)
        {
            m_work->start();
        }

        virtual ~SocketHandler()
        {
            if (m_work)
            {
                m_work->stop();
                m_work->wait(3000);
            }
        }

        virtual void readReady(Net::Socket* socket)
        {
        }

        void setWorkThread(base::WorkThread* work)
        {
            m_work = work;
            m_work->start();
        }
        base::WorkThread* getWorkThread()
        {
            return m_work;
        }
    private:
        base::WorkThread *m_work;

};


class IOManager
{
    public:
        IOManager();
        ~IOManager();

        bool addSocket(Net::Socket *socket, SocketHandler *handler);

        bool removeSocket(Net::Socket* socket);

        int readSocket(Net::Socket *socket, char* s, int length);

        int writeSocket(Net::Socket *socket, const char* s, int length);

        int readSocketAvalible(Net::Socket *socket);

        void run(void);

    private:
        bool m_running;
        WorkThread* m_thread;
        struct SocketNode
        {
            public:
                Net::Socket* m_socket;
                base::SocketHandler* m_handler;
                base::RingBuffer m_read;
                base::RingBuffer m_write;

                char* m_readLeft;
                int   m_readSign;
                int   m_readLen;

                char* m_writeLeft;
                int   m_writeSign;
                int   m_writeLen;

                SocketNode(Net::Socket *socket, SocketHandler *handler) :
                    m_socket(socket),
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
        };

        std::vector<SocketNode*> m_sockets;

        /*add - delete - search*/
        void addSocketNode(Net::Socket* socket, base::SocketHandler* handler);
        bool deleteSocketNode(Net::Socket* socket);
        SocketNode* searchSocketNode(Net::Socket* socket);
};

}
#endif
