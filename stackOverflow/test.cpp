#include <cstdlib>
#include <vector>

#include <iostream>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>

class TestTimer
{

    public:
        TestTimer(const std::string & name) : name(name),
        start(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time())
        {

        }


        ~TestTimer()
        {

            using namespace std;
            using namespace boost;

            posix_time::ptime now(date_time::microsec_clock<posix_time::ptime>::local_time());
            posix_time::time_duration d = now - start;

            cout << name << " completed in " << d.total_milliseconds() / 1000.0 <<
                " seconds" << endl;
        }

    private:
        std::string name;
        boost::posix_time::ptime start;
};

struct Pixel
{
    static int count;
    static int count2;
    Pixel()
    {
        count++;
    }

    Pixel(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b)
    {
    }
    Pixel(const Pixel& )
    {
        count2++;
    }

    unsigned char r, g, b;
};

int Pixel :: count = 0;
int Pixel :: count2 = 0;


void UseVector()
{
    TestTimer t("UseVector");

    int dimension = 999;

    std::cout << Pixel::count << " " << Pixel::count2 << std::endl;
    std::vector<Pixel> pixels(dimension * dimension);

    std::cout << Pixel::count << " " << Pixel::count2 << std::endl;
    for(int i = 0; i < 1000; ++i)
    {
        typedef std::vector<Pixel>::iterator PixIte;
        for(PixIte ite = pixels.begin(); ite != pixels.end(); ++ite)
        {
            ite->r = 255;
            ite->g = 0;
            ite->b = 0;
        }
    }
}

void UseVectorPushBack()
{
    TestTimer t("UseVectorPushBack");

    for(int i = 0; i < 1000; ++i)
    {
        int dimension = 999;

        std::vector<Pixel> pixels;
        pixels.reserve(dimension * dimension);

        for(int i = 0; i < dimension * dimension; ++i)
            pixels.push_back(Pixel(255, 0, 0));
    }
}

void UseArray()
{
    TestTimer t("UseArray");
    int dimension = 999;

    Pixel *pixels = new Pixel[dimension * dimension];
    for(int i = 0; i < 1000; ++i)
    {

        //  Pixel * pixels = (Pixel *)malloc(sizeof(Pixel) * dimension * dimension);

        for(int i = 0 ; i < dimension * dimension; ++i)
        {
            pixels[i].r = 255;
            pixels[i].g = 0;
            pixels[i].b = 0;
        }

        //       free(pixels);
    }
    delete [] pixels;
}

int main()
{
    TestTimer t1("The whole thing");

    UseVector();
    UseArray();
 //   UseVector1();
   // UseVectorPushBack();

    return 0;
}
