#ifndef __DECLARE_HPP__
#define __DECLARE_HPP__

namespace declare
{
    class Declare
    {
        private:
            int count;

            Declare(Declare&);
            Declare& operator= (Declare&);
        public:
            explicit Declare(int a)
            {
                this->count = a;
            }
            virtual ~Declare()
            {

            }
    };
};

#endif
