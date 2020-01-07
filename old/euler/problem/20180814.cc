/**
 *
 * @author      novemberizing
 * @date        2018. 8. 13.
 */

#include "20180814.hh"

#include <novemberizing/integer.hh>
#include <novemberizing/function.hh>

using namespace novemberizing;

static integer first = 0;
static integer second = 1;

integer calculate_next_fibonacci_numbers()
{
    integer n = first + second;
    first = second;
    second = n;
    return n;
}

integer calculate_next_fibonacci_numbers_1()
{
    integer n = 4 * second + first;
    first = second;
    second = n;
    return n;
}

void iticworld_euler_20180814_0()
{
    first = 0;
    second = 1;
    integer total = 0;
    integer n = 0;
    while(n < 4000000)
    {
        n = calculate_next_fibonacci_numbers();
        if(n % 2 == 0)
        {
            total += n;
        }
    }
    printf("%s\n", integer::to::hexadecimal(total).v());
}

void iticworld_euler_20180814_1()
{
    first = 2;
    second = 8;
    integer total = first + second;
    integer n = calculate_next_fibonacci_numbers_1();
    while(n < 4000000)
    {
        total += n;
        n = calculate_next_fibonacci_numbers_1();
    }
    printf("%s\n", integer::to::hexadecimal(total).v());
}
