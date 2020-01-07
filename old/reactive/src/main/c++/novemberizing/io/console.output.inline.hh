#ifndef   __NOVEMBERIZING_IO_CONSOLE__OUTPUT__INLINE__HH__
#define   __NOVEMBERIZING_IO_CONSOLE__OUTPUT__INLINE__HH__

#include <novemberizing/io/console.hh>

namespace novemberizing { namespace io {

inline console::output::output(void) : __buffer(4096)
{
    __descriptor = STDOUT_FILENO;
    on();
    open();
}

inline console::output::~output(void)
{
    close();
}

inline buffers::List & console::output::buffer(void) { return __buffer; }

inline type::int64 console::output::read(void){ return Success; }

inline int console::output::open(void)
{
    Descriptor::alives.set(this);
    return Success;
}

inline int console::output::close(void)
{
    Descriptor::alives.del(this);
    return Success;
}

inline bool console::output::should(EventType type) const
{
    if(type==Write)
    {
        return true;
    }
    else if(type==Close)
    {
        return __registered==Close;
    }
    return false;
}

inline type::int64 console::output::write(const type::byte * bytes,type::size length)
{
    __buffer.append(bytes,length);
    return write();
}

inline type::int64 console::output::write(void)
{
    type::size len = 0;
    type::byte * bytes = __buffer.front(len);
    type::int64 n = ::write(__descriptor,bytes,len);
    if(n>0)
    {
        __buffer.erase(0,n);
    }
    else if(n==0)
    {
        n = Success;
    }
    else
    {
        n = Success;
    }
    return n;
}

inline console::output & console::output::operator<<(const Buffer & buf)
{
    __buffer.append(buf);
    return *this;
}

inline console::output & console::output::operator<<(char c)
{
    __buffer.append(c);
    return *this;
}

inline console::output & console::output::operator<<(const char * str)
{
    __buffer.append(str);
    return *this;
}

inline console::output & console::output::operator<<(console::output & (*op)(console::output &))
{
    return op(*this);
}

inline console::output & console::output::flush(void)
{
    while(__buffer.size()>0){ write(); }
    return *this;
}

inline console::output & console::output::append(const type::byte * bytes,type::size position,type::size length)
{
    __buffer.append(bytes,position,length);
    return *this;
}

// inline type::size console::output::remain(void) const { return }

} }

#endif // __NOVEMBERIZING_IO_CONSOLE__OUTPUT__INLINE__HH__
