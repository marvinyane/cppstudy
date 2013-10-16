#include <string.h>
#include <utility>
#include <iostream>

class mString
{
    public:
        mString()
            :data_(new char[1])
        {
            *data_ = 0;
        }

        mString(const char* str)
            :data_(new char[strlen(str) + 1])
        {
            strcpy(data_, str);
        }

        mString(const mString& rhs)
            :data_(new char[rhs.size() + 1])
        {
            strcpy(data_, rhs.c_str());
        }

        ~mString()
        {
            delete [] data_;
        }

        mString& operator=(const mString& rhs)
        {
            mString tmp(rhs);
            swap(tmp);
            return *this;
        }

        size_t size()const
        {
            return strlen(data_);
        }

        const char* c_str()const
        {
            return data_;
        }

        void swap(mString& rhs)
        {
            std::swap(data_, rhs.data_);
        }

        void print()
        {
            std::cout << data_ << std::endl;
        }
    
    private:
        char* data_;

};


int main()
{
    mString str("hello");
    
    mString str1 = str;
    str1.print();

    mString str2(str1);
    str2.print();

    mString str3;
}
