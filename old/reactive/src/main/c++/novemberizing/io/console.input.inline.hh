#ifndef   __NOVEMBERIZING_IO_CONSOLE__INPUT__INLINE__HH__
#define   __NOVEMBERIZING_IO_CONSOLE__INPUT__INLINE__HH__

#include <unistd.h>

namespace novemberizing { namespace io {

inline console::input::input(void) : __buffer(4096)
{
    __descriptor = STDIN_FILENO;
    on();
    open();
}

inline console::input::~input(void)
{
    close();
}

inline type::int64 console::input::read(void)
{
    char data[4096];
    type::int64 n = ::read(__descriptor,data,4096);
    if(n>0)
    {
        __buffer.append(data,0,n);
    }
    else if(n==0)
    {
        WARNING_LOG("fail to ::read(...) return 0");
        n = Success;
    }
    else
    {
        if(errno!=EAGAIN)
        {
            WARNING_LOG("fail to ::read(...) caused by %d",errno);
        }
        n = Success;
    }
    if(onRead!=nullptr){ onRead(*this, __buffer); }
    return n;
}

inline bool console::input::should(EventType type) const
{
    if(type==Read)
    {
        return true;
    }
    else if(type==Close)
    {
        return __registered==Close;
    }
    return false;
}

inline type::int64 console::input::write(void) { return Success; }
inline type::int64 console::input::write(const type::byte * bytes,type::size length){ return Success; }

inline int console::input::open(void)
{
    Descriptor::alives.set(this);
    return Success;
}

inline int console::input::close(void)
{
    Descriptor::alives.del(this);
    return Success;
}

inline buffers::Continuous & console::input::buffer(void){ return __buffer; }

} }

#endif // __NOVEMBERIZING_IO_CONSOLE__INPUT__INLINE__HH__
