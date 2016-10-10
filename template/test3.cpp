#include <iostream>

template<bool C, typename LSH, typename RHS> struct CompileTimeIfElse;
template<typename LHS, typename RHS> 
struct CompileTimeIfElse<true,  LHS, RHS> 
{
     typedef LHS TYPE; 
};

template<typename LHS, typename RHS> 
struct CompileTimeIfElse<false, LHS, RHS> 
{
     typedef RHS TYPE; 
};


int main()
{
    CompileTimeIfElse<1 == 1, int, float>::TYPE a = 3;

    return 0;
}
