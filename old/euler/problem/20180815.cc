/**
 *
 * @author      novemberizing
 * @date        2018. 8. 13.
 */

#include "20180815.hh"

#include <novemberizing/linked/list.hh>
#include <novemberizing/integer.hh>

using namespace novemberizing;

void iticworld_euler_20180815_0()
{
    linked::list<integer> primes;
    integer total = 600851475143UL;
    for(integer i = 2; i <= total; i++)
    {
        bool is = true;
        primes.until([i, &is](const integer & v){
            return !(is = (i % v != 0));
        });

        if(is)
        {
            primes.add(i);
            while(total % i == 0)
            {
                total = total / i;
            }
        }
    }
    integer x = primes.back() * primes.back();

    printf("max: %s\n", integer::to::hexadecimal(primes.back()).v());
    printf("max: %s\n", integer::to::hexadecimal(x).v());
}