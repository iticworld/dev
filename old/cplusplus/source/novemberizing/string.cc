/**
 *
 * @author      novemberizing <developer@novemberizing.net>
 * @since       0.0.1
 * @date        2018. 6. 3.
 */

#include <string.h>

#include <novemberizing/string.hh>

namespace novemberizing
{
    uint64 string::length(const char * s)
    {
        return ::strlen(s);
    }


    bool string::equal(const string & o) const
    {
        return __size == o.__size && memcmp(__data, o.__data, __size) == 0;
    }

    bool string::equal(string && o) const
    {
        return __size == o.__size && memcmp(__data, o.__data, __size) == 0;
    }

    bool string::equal(const char * s) const
    {
        uint64 len = (s!=nullptr ? string::length(s) : 0);
        return s!=nullptr && len == __size && memcmp(__data, s, __size) == 0;
    }

    bool string::equal(char c) const
    {
        return __size == 1 && __data[0] == c;
    }

    int string::compare(const string & o) const noexcept
    {
        int out = strncmp(__data, o.__data, __size < o.__size ? __size : o.__size);
        if(out  == 0)
        {
            if(__size != o.__size)
            {
                out = (__size > o.__size ? 1 : -1);
            }
        }
        return out;
    }

    int string::compare(uint64 offset, uint64 n, const string & o) const
    {
        if(__size < offset)
        {
            offset = __size;
            throw exception();
        }
        n = (__size - offset < n ? __size - offset : n);
        int out = strncmp(&__data[offset], o.__data, n < o.__size ? n : o.__size);
        if(out == 0)
        {
            if(n != o.__size)
            {
                out = (n > o.__size ? 1 : -1);
            }
        }
        return out;
    }

    int string::compare(uint64 offset, uint64 n, const string & o, uint64 pos, uint64 len) const
    {
        if(__size < offset)
        {
            offset = __size;
            throw exception();
        }
        if(pos < o.__size)
        {
            pos = o.__size;
            throw exception();
        }
        n = (__size - offset < n ? __size - offset : n);
        len = (o.__size - pos < len ? o.__size - pos : len);
        int out = strncmp(&__data[offset], &o.__data[pos], n < len ? n : len);
        if(out == 0)
        {
            if(n != len)
            {
                out = (n > len ? 1 : -1);
            }
        }
        return out;
    }

    int string::compare(const char * s) const
    {
        uint64 len = (s != nullptr ? strlen(s) : 0);
        int out = strncmp(__data, s, __size < len ? __size : len);
        if(out == 0)
        {
            if(__size != len)
            {
                out = (__size > len ? 1 : -1);
            }
        }
        return out;
    }

    int string::compare(uint64 offset, uint64 n, const char * s) const
    {
        return compare(offset, n, s, s != nullptr ? strlen(s) : 0);
    }

    int string::compare(uint64 offset, uint64 n, const char * s, uint64 len) const
    {
        if(__size < offset)
        {
            offset = __size;
            throw exception();
        }
        n = (__size - offset < n ? __size - offset : n);
        len = (s != nullptr ? len : 0);
        int out = strncmp(__data, s, n < len ? n : len);
        if(out == 0)
        {
            if(n != len)
            {
                out = (n > len ? 1 : -1);
            }
        }
        return out;
    }
}



