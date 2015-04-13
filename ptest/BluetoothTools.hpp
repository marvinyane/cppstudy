#ifndef __BLUETOOTHTOOLS_HPP__
#define __BLUETOOTHTOOLS_HPP__

#include <cstring>
#include <cstdio>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

class BDADDR
{
    private:
        uint8 addr[6];

    public:
        BDADDR()
        {
            memset(this->addr, 0, sizeof(addr));
        }

        BDADDR(uint8* addr)
        {
            memcpy(this->addr, addr, 6);
        }

        BDADDR(uint8 a, uint8 b, uint8 c, uint8 d, uint8 e, uint8 f)
        {
            this->addr[0] = a;
            this->addr[1] = b;
            this->addr[2] = c;
            this->addr[3] = d;
            this->addr[4] = e;
            this->addr[5] = f;
        } 
        
        BDADDR(const BDADDR& t)
        {
            memcpy(this->addr, t.addr, 6);
        }
        
        BDADDR& operator = (BDADDR& t);
        bool operator == (const BDADDR& t)const;
        bool operator == (const int zero)const;

        void Display();

        virtual ~BDADDR()
        {
            //
        }
};

BDADDR& BDADDR::operator=(BDADDR& t)
{
    memcpy(this->addr, t.addr, 6);
}

bool BDADDR::operator==(const BDADDR& t)const
{
    if (memcmp(this->addr, t.addr, 6) == 0)
    {
        return true;
    }

    return false;
}

bool BDADDR::operator==(const int zero)const
{
    if (addr[0] == 0 
            && this->addr[1] == 0
            && this->addr[2] == 0
            && this->addr[3] == 0
            && this->addr[4] == 0
            && this->addr[5] == 0
            )
    {
        return true;
    }

    return false;
}

void BDADDR::Display()
{
    uint8 i = 0;
    printf("-------------------------- \n");
    for(; i < 6; i++)
    {
        printf("%.2x ", this->addr[i]);
    }
    printf("\n-------------------------- \n");
}

#endif
