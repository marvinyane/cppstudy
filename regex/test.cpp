// regex_match example
#include <iostream>
#include <string>
#include <regex>

int main ()
{
    std::string s ("StateMachine change state from StatePrepare to StatePreload.");
    
    try 
    {
        std::regex integer("(\\+|-)?[[:digit:]]+");
    }
    catch (std::regex_error& e)
    {
        std::cout << e.what() << " \n code : " << e.code() << std::endl;
    }


    //std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    //std::regex_match (s,sm,e);
    //std::cout << "string object with " << sm.size() << " matches\n";

    //std::cout << "the matches were: ";
    //for (unsigned i=0; i<sm.size(); ++i) {
        //std::cout << "[" << sm[i] << "] ";
    //}

    //std::cout << std::endl;

    return 0;
}
