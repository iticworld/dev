#include "descriptor.hh"

namespace novemberizing { namespace io {

Descriptor::Map Descriptor::alives;

Descriptor::Descriptor(void)
{
    FUNCTION_START("");

    __descriptor = Invalid;
    __registered = 0x00000000;

    FUNCTION_END("");
}

Descriptor::~Descriptor(void)
{
    FUNCTION_START("");

    FUNCTION_END("");
}

bool Descriptor::nonblock(bool v)
{
    bool ret = false;
    int flags = ::fcntl(__descriptor, F_GETFL, 0);
    if(flags>=0)
    {
        if(v)
        {
            flags |= O_NONBLOCK;
        }
        else
        {
            flags &= (~O_NONBLOCK);
        }
        if(!(ret = (::fcntl(__descriptor, F_SETFL, flags | O_NONBLOCK)==Success)))
        {
            WARNING_LOG("fail to ::fcntl(...) caused by %d",errno);
        }
    }
    else
    {
        WARNING_LOG("fail to ::fcntl(...) caused by %d",errno);
    }
    return ret;
}

} }
