/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 08. 18.
 */

#include "20180818.hh"

#include <novemberizing/integer.hh>

using namespace novemberizing;

integer f1(const integer & n)
{
    return n * (n + 1) / 2;
}

integer f2(const integer & n)
{
    return n * (2 * n + 1) * (n + 1) / 6;
}

void iticworld_euler_20180818_0()
{
    printf("%s\n", integer::to::decimal(f1(100) * f1(100) - f2(100)).v());
}
