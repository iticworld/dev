/**
 *
 * @author      novemberizing
 * @date        2018. 8. 13.
 */

#include "20180813.hh"

#include <novemberizing/integer.hh>
#include <novemberizing/function.hh>

using namespace novemberizing;

/**
 * @see https://projecteuler.net/problem=1
 * @see https://en.wikipedia.org/wiki/Arithmetic_progression
 */
extern void iticworld_euler_20180813_0()
{
    integer total = 0;
    for(integer x = 0; x < 1000; ++x)
    {
        if(x % 3 == 0 || x % 5 == 0)
        {
            total += x;
        }
    }
    printf("%s\n", integer::to::hexadecimal(total).v());
}

extern void iticworld_euler_20180813_1()
{
    integer max = 999;
    function::single<type::uint64, integer> f = [max](type::uint64 n){
        integer p = max / n;
        return n * (p * (p + 1)) / 2;
    };

    integer total = f(3) + f(5) - f(15);
    printf("%s\n", integer::to::hexadecimal(total).v());
}
