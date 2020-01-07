/**
 *
 * @author      novemberizing
 * @since       0.0.2
 * @date        2018. 8. 20.
 */

#include "20180820.hh"

#include <novemberizing/integer.hh>
#include <novemberizing/linked/list.hh>

using namespace novemberizing;

linked::list<integer> primes;

void iticworld_euler_20180820_0()
{
    for(integer i = 2;primes.size() < 10001;++i)
    {
        bool save = true;
        primes.until([&i, &save](const integer & v){
            return !(save = (i % v != 0));
        });
        if(save)
        {
            primes.add(i);
            printf("%ld => %s\n", primes.size(), integer::to::decimal(i).v());
        }
    }
    printf("%s\n", integer::to::decimal(primes.back()).v());
}