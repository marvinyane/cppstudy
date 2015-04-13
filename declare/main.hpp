#ifndef __MAIN_HPP__
#define __MAIN_HPP__

namespace declare
{
    class Declare;

    class Main
    {
        private:
            
            Main(Main&);
            Main& operator= (Main&);

        public:
            explicit Main();
            virtual ~Main();

            Declare& getDeclare();

            void setDeclare(Declare&);
    };
};

#endif
