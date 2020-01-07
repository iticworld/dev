/**
 *
 * @author      novemberizing
 * @date        2018. 8. 16.
 */

#include "20180816.hh"

#include <novemberizing/linked/list.hh>
#include <novemberizing/integer.hh>

using namespace novemberizing;

#include <cstdio>


static integer f(const integer & n)
{
    return 11 * (9091 - 90 * ((n + 1)/11) + 100 * n);
}

void iticworld_euler_20180816_0()
{
    for(integer i = 0; i < 50; i++)
    {
        printf("%s\n", integer::to::decimal(f(i)).v());
    }
    integer max = 0;
    integer _x = 0;
    integer _y = 0;
    for(integer j = 999; j >= 100; --j)
    {
        for(integer i = 990; i > 0; i-=11)
        {
            integer n = i * j;
            if(n < max)
            {
                break;
            }
            string s = integer::to::decimal(n);
            if(s.size() % 2 == 0)
            {
                bool same = true;
                for(int k = 0; k < s.size() / 2; k++)
                {
                    // printf("%c/%c\n", s[k], s[s.size() - k - 1]);
                    if(s[k] != s[s.size() - k - 1])
                    {
                        same = false;
                        break;
                    }
                }
                if(same)
                {
                    if(max < n)
                    {
                        max = n;
                        _x = i;
                        _y = j;
                    }

                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    printf("%s * %s = %s\n", integer::to::decimal(_x).v(), integer::to::decimal(_y).v(), integer::to::decimal(max).v());
}
