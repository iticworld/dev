/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__LOG__HH__
#define   __NOVEMBERIZING__LOG__HH__

#include <novemberizing.hh>
#include <novemberizing/string.hh>

namespace novemberizing
{
    namespace log
    {
        inline void e(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void w(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void c(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void n(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void i(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void d(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void v(const string & tag, const string & file, uint32 line, const string & func, const string & message);
        inline void f(const string & tag, const string & file, uint32 line, const string & func, const string & message);
    }
}

#include <novemberizing/log.hp>

#endif // __NOVEMBERIZING__LOG__HH__
