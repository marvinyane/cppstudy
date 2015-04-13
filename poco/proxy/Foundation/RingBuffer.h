#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#define NULL 0

namespace base
{

class RingBuffer
{
    public:
        RingBuffer()
        {
            Record* r = new Record;
            m_head = r;
            m_tail = r;
            m_size = 0;
        }
        ~RingBuffer()
        {
            while (m_head)
            {
                delete m_head;
                m_head = m_head->next;
            }

            m_head = NULL;
            m_tail = NULL;
            m_size = 0;
        }

        void push(const char *s, int len)
        {
            Record* r = new Record(s, len);

            Record* q = m_tail;
            Record* oldq = q;

            do
            {
                while (q->next != NULL)
                {
                    q = q->next;
                }
            }while (!CompareAndSet(&(q->next), NULL, r));

            CompareAndSet(&m_tail, oldq, r);
            FetchAndAdd(&m_size, len);
        }

        char* pop(int *length)
        {
            Record* p = NULL;
            do
            {
                p = m_head;
                if (p->next == NULL)
                {
                    return false;
                }
            }while (!CompareAndSet(&m_head, p, p->next));

            const char *s  = p->next->s;
            *length = p->next->len;
            FetchAndSub(&m_size, p->next->len);

            delete p;
            return const_cast<char*>(s);
        }

        int size()
        {
            return m_size;
        }

    private:
        struct Record
        {
            public:
                const char *s;
                int len;
                Record* next;

                Record():s(NULL),next(NULL),len(0)
                {
                }
                Record(const char* s, int len):s(s),next(NULL),len(len)
                {
                }
        };

        Record *m_head;
        Record *m_tail;
        int m_size;
        
        bool CompareAndSet(Record** r, Record* o, Record* n)
        {
#if 1
            return __sync_bool_compare_and_swap(r, o, n);
#else
            return false;
#endif
        }

        int FetchAndSub(int* v, int s)
        {
            return __sync_fetch_and_sub(v, s);
        }

        int FetchAndAdd(int* v, int s)
        {
            return __sync_fetch_and_add(v, s);
        }

};

}//namespace 

#endif
