#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

#include "RingBuffer.h"
#include "WorkThread.h"

#include "Socket.h"
#include "SocketAddress.h"

#include "Mutex.h"

#include <string>

namespace base
{

class WorkThread;

class SocketHandler
{
    public:
        SocketHandler(WorkThread* work):m_work(work){}
        virtual ~SocketHandler(){}

        virtual void readReady(Net::Socket* socket)=0;
        virtual void disconnected(Net::Socket* socket)=0;

        WorkThread* getWorkThread()
        {
            return m_work;
        }
    protected:
        WorkThread* m_work;
};


class IOManager
{
    public:
        enum State
        {
            Listen,
            Connected,
            Closing,
        };

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

                IOManager::State m_state;

                SocketNode(Net::Socket *socket, SocketHandler *handler, IOManager::State s) :
                    m_socket(socket),
                    m_handler(handler),
                    m_read(),
                    m_write(),
                    m_readLeft(NULL),
                    m_readSign(0),
                    m_readLen(0),
                    m_writeLeft(NULL),
                    m_writeSign(0),
                    m_writeLen(0),
                    m_state(s)

                {
                }

                bool stateToSelect()
                {
                    return m_state == IOManager::Listen || m_state == IOManager::Connected;
                }

                bool stateToClose()
                {
                    return m_state == IOManager::Closing;
                }

                void clearWriteLeft()
                {
                    if (m_writeLeft)
                    {
                        delete [] m_writeLeft;
                    }
                    m_writeLeft = NULL;
                    m_writeSign = 0;
                    m_writeLen = 0;
                }
                
                void clearReadLeft()
                {
                    if (m_readLeft)
                    {
                        delete [] m_readLeft;
                    }
                    m_readLeft = NULL;
                    m_readSign = 0;
                    m_readLen = 0;
                }
        };

        std::vector<SocketNode*> m_sockets;
        Mutex                    m_mutex; // lock for m_sockets


        /*add - delete - search*/
        void addSocketNode(Net::Socket* socket, base::SocketHandler* handler, IOManager::State);
        SocketNode* searchSocketNode(Net::Socket* socket);
};

}
#endif
