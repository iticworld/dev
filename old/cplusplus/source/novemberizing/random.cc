/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 10
 */

#include "random.hh"
#include "novemberizing/exception.hh"

namespace novemberizing
{
    unsigned int random::__seed = -1;

    int random::__get()
    {
#ifndef   WIN32
        if(random::__seed == -1)
        {
            srand(random::__seed = (unsigned int) time(nullptr));
        }
        return rand();
#else  // WIN32
        throw exception();
#endif // WIN32
    }

    random::random()
    {
    }

    random::random(const random & o)
    {
    }

    random::random(random && o) noexcept
    {
    }

    random::~random()
    {
    }

    random & random::operator=(const random & o)
    {
        return *this;
    }

    random & random::operator=(random && o) noexcept
    {
        return *this;
    }
//    public:     ;
//    public:     ;
}
