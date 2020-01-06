#ifndef   __NOVEMBERIZING_IO__CONSOLE__INLINE__HH__
#define   __NOVEMBERIZING_IO__CONSOLE__INLINE__HH__

namespace novemberizing { namespace io {

inline console::output & console::flush(console::output & o)
{
    while(o.__buffer.size()>0){ o.write(); }
    return o;
}

inline console::output & console::lock(console::output & o)
{
    o.lock();
    return o;
}

inline console::output & console::unlock(console::output & o)
{
    o.flush();
    o.unlock();
    return o;
}

inline console::output & console::endl(console::output & o){ return o<<'\n'<<console::flush; }

inline console::console(void)
{
}

inline console::~console(void)
{
}

} }

#endif // __NOVEMBERIZING_IO__CONSOLE__INLINE__HH__
