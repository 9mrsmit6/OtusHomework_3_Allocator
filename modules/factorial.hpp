#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <cassert>

namespace Utils
{
    int factorial(int n)
    {
        assert(n>=0);
        return n==0 ?  1 : (n*factorial(n-1)) ;
    }


}

#endif // FACTORIAL_HPP







