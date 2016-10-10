#include <iostream>

namespace test
{
    class Test
    {
        public:
            Test();
            ~Test();

            virtual int add(int a, int b);

            virtual void result(int a) = 0;

            int sub(int a, int b);

            int name()
            {
                return 1;
            }

        private:
            int a;
    };
}
