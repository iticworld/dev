/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 8. 17.
 */

#include "20180817.hh"

#include <novemberizing/integer.hh>
#include <novemberizing/linked/list.hh>
#include <novemberizing/array/list.hh>

using namespace novemberizing;

static linked::list<integer> primes;

static void f(const integer & total)
{
    for(integer i = 2; i <= total; i++)
    {
        bool is = true;
        primes.until([i, &is](const integer & v){
            return !(is = (i % v != 0));
        });

        if(is)
        {
            primes.add(i);
        }
    }
}

static void f2(const integer & max)
{
    f(max);

    integer total = 1;
    primes.each([&max, &total](const integer & v){
        integer n = v;
        integer k = 0;
        do {
            k = n * v;
            if(k <= max)
            {
                n = k;
            }
        } while(k <= max);
        total *= n;
    });
    printf("%s\n", integer::to::decimal(total).v());
}

void iticworld_euler_20180817_0()
{
    f2(10);
    f2(20);
}
