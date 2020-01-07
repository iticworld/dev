/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING__STRING__HH__
#define   __NOVEMBERIZING__STRING__HH__

#include <novemberizing.hh>
#include <novemberizing/memory.hh>
#include <novemberizing/exception.hh>

namespace novemberizing
{
    class string
    {
    public:     static const type::size page = 64;
    public:     static string dup(const string & o)
                {
                    return string(o);
                }
    public:     static string sub(const string & o, type::size pos)
                {
                    return string(o, pos);
                }
    public:     static string sub(const string & o, type::size pos, type::size len)
                {
                    return string(o, pos, len);
                }
    public:     static type::size length(const type::character * s)
                {
                    return __novemberizing_string_length(s);
                }
    public:     static bool different(const string & x, const string & y) noexcept
                {
                    return x.__size != y.__size || compare(x.__data, y.__data, x.__size)!=0;
                }
    public:     static bool different(const type::character * x, const string & y)
                {
                    type::size len = string::length(x);
                    return len != y.__size || compare(x, y.__data, len)!=0;
                }
    public:     static bool different(const string & x, const type::character * y)
                {
                    type::size len = string::length(y);
                    return x.__size != len || compare(x.__data, y, x.__size)!=0;
                }
    public:     static bool different(const type::character * x, const type::character * y)
                {
                    type::size len = string::length(x);
                    return len == string::length(y) && compare(x, y, len)!=0;
                }
    public:     static bool equal(const string & x, const string & y) noexcept
                {
                    return x.__size == y.__size && compare(x.__data, y.__data, x.__size) == 0;
                }
    public:     static bool equal(const type::character * x, const string & y)
                {
                    type::size len = string::length(x);
                    return len == y.__size && compare(x, y.__data, len) == 0;
                }
    public:     static bool equal(const string & x, const type::character * y)
                {
                    type::size len = string::length(y);
                    return x.__size == len && compare(x.__data, y, x.__size) == 0;
                }
    public:     static bool equal(const type::character * x, const type::character * y)
                {
                    type::size len = string::length(x);
                    return len == string::length(y) && compare(x, y, len)==0;
                }
    public:     static type::int32 compare(const string & x, const string & y) noexcept
                {
                    type::int32 res = __novemberizing_string_compare(x.__data, y.__data, x.__size < y.__size ? x.__size : y.__size);
                    return x.__size == y.__size || res != 0 ? res : x.__size >  y.__size;
                }
    public:     static type::int32 compare(const type::character * x, const string & y)
                {
                    type::size len = string::length(x);
                    type::int32 res = __novemberizing_string_compare(x, y.__data, len < y.__size ? len : y.__size);
                    return len == y.__size || res != 0 ? res : len >  y.__size;
                }
    public:     static type::int32 compare(const string & x, const type::character * y)
                {
                    type::size len = string::length(y);
                    type::int32 res = __novemberizing_string_compare(x.__data, y, x.__size < len ? x.__size : len);
                    return x.__size == len || res != 0 ? res : x.__size >  len;
                }
    public:     static type::int32 compare(const type::character * x, const type::character * y, type::size n)
                {
                    return __novemberizing_string_compare(x, y, n);
                }
    public:     static string format(const char * fmt, ...);
    protected:  type::character * __data;
    protected:  type::size __size;
    protected:  type::size __capacity;
    public:     type::size capacity() const
                {
                    return __capacity;
                }
    public:     type::size size() const
                {
                    return __size;
                }
    public:     const type::character * v() const
                {
                    return __data;
                }
    public:     string & assign(const string & o)
                {
                    if(&o != this)
                    {
                        __size = o.__size;
                        __capacity = o.__capacity;
                        __data = memory::allocate<type::character>(__data, __capacity);
                        memory::copy<type::character>(__data, o.__data, __size);
                        __data[__size] = 0;
                    }
                    return *this;
                }
    public:     string & assign(const string & o, type::size position)
                {
                    if(&o != this)
                    {
                        if(position < o.__size)
                        {
                            __size = o.__size - position;
                            __capacity = (__size / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::copy<type::character>(__data, &o.__data[position], __size);
                            __data[__size] = 0;
                        }
                        else if(position == o.__size)
                        {
                            __size = 0;
                            __capacity = (__size / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            __data[__size] = 0;
                        }
                        else
                        {
                            throw exception();  // NOLINT
                        }
                    }
                    return *this;
                }
    public:     string & assign(const string & o, type::size position, type::size length)
                {
                    if(&o != this)
                    {
                        if(position < o.__size)
                        {
                            if(o.__size - position < length)
                            {
                                NOTICE_LOG("o.__size - position < length");
                                length = o.__size - position;
                            }
                            __size = length;
                            __capacity = (__size / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::copy<type::character>(__data, &o.__data[position], __size);
                            __data[__size] = 0;
                        }
                        else if(position == o.__size)
                        {
                            __size = 0;
                            __capacity = (__size / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            __data[__size] = 0;
                        }
                        else
                        {
                            throw exception();  // NOLINT
                        }
                    }
                    return *this;
                }
    public:     string & assign(string && o) noexcept
                {
                    if(&o != this)
                    {
                        __data = o.__data;
                        __size = o.__size;
                        __capacity = o.__capacity;

                        o.__data = nullptr;
                        o.__size = 0;
                        o.__capacity = 0;
                    }
                    return *this;
                }
    public:     string & assign(const type::character * s)
                {
                    __size = string::length(s);
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    if(__size > 0)
                    {
                        memory::copy<type::character>(__data, s, __size);
                    }
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & assign(const type::character * s, type::size length)
                {
                    if(s == nullptr)
                    {
                        if(length > 0)
                        {
                            WARNING_LOG("length > 0");
                        }
                        __size = 0;
                    }
                    else
                    {
                        __size = length;
                    }
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    if(__size > 0)
                    {
                        memory::copy<type::character>(__data, s, __size);
                    }
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & assign(type::character c)
                {
                    __size = 1;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __size);
                    __data[0] = c;
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & assign(type::character c, type::size length)
                {
                    __size = length;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __size);
                    if(__size > 0)
                    {
                        memory::set(__data, c, __size);
                    }
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & append(const string & o)
                {
                    if(&o != this)
                    {
                        type::size size = __size + o.__size;
                        __capacity = (size / page + 1) * page;
                        __data = memory::allocate<type::character>(__data, __capacity);
                        memory::copy(&__data[__size], o.__data, o.__size);
                        __size = size;
                        __data[__size] = 0;
                    }
                    else
                    {
                        return append(string(o));
                    }
                    return *this;
                }
    public:     string & append(const string & o, type::size position)
                {
                    if(&o != this)
                    {
                        if(position < o.__size)
                        {
                            type::size length = o.__size - position;
                            type::size size = __size + length;
                            __capacity = (size / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::copy(&__data[__size], &o.__data[position], length);
                            __size = size;
                            __data[__size] = 0;
                        }
                        else
                        {
                            if(position > o.__size)
                            {
                                WARNING_LOG("position > o.__size");
                            }
                        }
                    }
                    else
                    {
                        return append(string(o), position);
                    }
                    return *this;
                }
    public:     string & append(const string & o, type::size position, type::size length)
                {
                    if(&o != this)
                    {
                        if(position < o.__size)
                        {
                            if(o.__size - position < length)
                            {
                                length = o.__size - position;
                            }
                            type::size size = __size + length;
                            __capacity = (size / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::copy(&__data[__size], &o.__data[position], length);
                            __size = size;
                            __data[__size] = 0;
                        }
                        else
                        {
                            if(position > o.__size)
                            {
                                WARNING_LOG("position > o.__size");
                            }
                        }
                    }
                    else
                    {
                        return append(string(o), position);
                    }
                    return *this;
                }
    public:     string & append(string && o)
                {
                    if(&o != this)
                    {
                        type::size size = __size + o.__size;
                        __capacity = (size / page + 1) * page;
                        __data = memory::allocate<type::character>(__data, __capacity);
                        memory::copy(&__data[__size], o.__data, o.__size);
                        __size = size;
                        __data[__size] = 0;
                    }
                    else
                    {
                        return append(string(o));
                    }
                    return *this;
                }
    public:     string & append(const type::character * s)
                {
                    type::size length = (s != nullptr ? string::length(s) : 0);
                    __capacity = ((__size + length) / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __capacity);
                    memory::copy<type::character>(&__data[__size], s, length);
                    __size += length;
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & append(const type::character * s, type::size length)
                {
                    if(s == nullptr && length > 0)
                    {
                        throw exception();  // NOLINT
                    }
                    length = (s != nullptr ? length : 0);
                    __capacity = ((__size + length) / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __capacity);
                    memory::copy<type::character>(&__data[__size], s, length);
                    __size += length;
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & append(type::character c)
                {
                    __capacity = ((__size + 1) / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __capacity);
                    __data[__size] = c;
                    __size += 1;
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & append(type::character c, type::size length)
                {
                    __capacity = ((__size + length) / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __capacity);
                    memory::fill<char>(&__data[__size], c, length);
                    __size += length;
                    __data[__size] = 0;
                    return *this;
                }
    public:     string & insert(type::size offset, const string & o)
                {
                    if(offset < __size)
                    {
                        if(o.__size > 0)
                        {
                            __capacity = ((__size + o.__size) / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + o.__size], &__data[offset], __size - offset);
                            memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                            __size += o.__size;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, const string & o, type::size pos)
                {
                    if(offset < __size)
                    {
                        type::size len = 0;
                        if(o.__size < pos)
                        {
                            throw exception();  // NOLINT
                        }
                        else
                        {
                            len = o.__size - pos;
                        }
                        if(len > 0)
                        {
                            __capacity = ((__size + len) / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + len], &__data[offset], __size - offset);
                            memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                            __size += len;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o, pos);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, const string & o, type::size pos, type::size len)
                {
                    if(offset < __size)
                    {
                        if(o.__size < pos)
                        {
                            throw exception();  // NOLINT
                        }
                        else
                        {
                            len = (len < o.__size - pos ? len : o.__size - pos);
                        }
                        if(len > 0)
                        {
                            __capacity = ((__size + len) / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + len], &__data[offset], __size - offset);
                            memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                            __size += len;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o, pos, len);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, string && o)
                {
                    if(offset < __size)
                    {
                        if(o.__size > 0)
                        {
                            __capacity = ((__size + o.__size) / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + o.__size], &__data[offset], __size - offset);
                            memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                            __size += o.__size;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(move(o));
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, const type::character * s)
                {
                    if(offset < __size)
                    {
                        type::size len = (s != nullptr ? string::length(s) : 0);
                        if(len > 0)
                        {
                            __capacity = ((__size + len) / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + len], &__data[offset], __size - offset);
                            memory::copy<type::character>(&__data[offset], s, len);
                            __size += len;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(s);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, const type::character * s, type::size len)
                {
                    if(offset < __size)
                    {
                        if(s == nullptr && len > 0)
                        {
                            throw exception();  // NOLINT
                        }
                        len = (s != nullptr ? len : 0);
                        if(len > 0)
                        {
                            __capacity = ((__size + len) / page + 1) * page;
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + len], &__data[offset], __size - offset);
                            memory::copy<type::character>(&__data[offset], s, len);
                            __size += len;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(s, len);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, type::character c)
                {
                    if(offset < __size)
                    {
                        __capacity = ((__size + 1) / page + 1) * page;
                        __data = memory::allocate<type::character>(__data, __capacity);
                        memory::move<type::character>(&__data[offset + 1], &__data[offset], __size - offset);
                        __data[offset] = c;
                        __size += 1;
                        __data[__size] = 0;
                    }
                    else if(offset == __size)
                    {
                        append(c);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & insert(type::size offset, type::character c, type::size len)
                {
                    if(offset < __size)
                    {
                        if(len > 0)
                        {
                            __capacity = ((__size + len) / page + 1) * page;  //capacity::get(__size + len, string::page);
                            __data = memory::allocate<type::character>(__data, __capacity);
                            memory::move<type::character>(&__data[offset + len], &__data[offset], __size - offset);
                            memory::fill<type::character>(&__data[offset], c, len);
                            __size += len;
                            __data[__size] = 0;
                        }
                    }
                    else if(offset == __size)
                    {
                        append(c, len);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & erase()
                {
                    __size = 0;
                    if(__data != nullptr)
                    {
                        __data[__size] = 0;
                    }
                    return *this;
                }
    public:     string & erase(type::size offset)
                {
                    if(offset == 0)
                    {
                        __size = 0;
                        if(__data != nullptr)
                        {
                            __data[__size] = 0;
                        }
                    }
                    else if(offset <= __size)
                    {
                        __size = offset;
                        __data[__size] = 0;
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & erase(type::size offset, type::size n)
                {
                    if(n > 0)
                    {
                        if(offset == 0)
                        {
                            if(n < __size)
                            {
                                memory::move<type::character>(__data, &__data[n], __size - n);
                                __size -= n;
                                __data[__size] = 0;
                            }
                            else
                            {
                                __size = 0;
                                if(__data != nullptr)
                                {
                                    __data[__size] = 0;
                                }
                            }
                        }
                        else if(offset <= __size)
                        {
                            if(offset + n < __size)
                            {
                                memory::move<type::character>(&__data[offset], &__data[offset + n], __size - offset - n);
                                __size -= n;
                                __data[__size] = 0;
                            }
                            else
                            {
                                __size = offset;
                                __data[__size] = 0;
                            }
                        }
                        else
                        {
                            throw exception();  // NOLINT
                        }
                    }
                    return *this;
                }
    public:     string & replace(type::size offset, type::size n, const string & o)
                {
                    if(offset < __size)
                    {
                        if(o.__size > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < o.__size)
                                {
                                    __capacity = ((__size + (o.__size - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                                    __size += (o.__size - n);
                                    __data[__size] = 0;
                                }
                                else if(n ==  o.__size)
                                {
                                    memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                                    __size -= (n - o.__size);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, o);
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }

    public:     string & replace(type::size offset, type::size n, const string & o, type::size pos)
                {
                    if(offset < __size)
                    {
                        type::size len = 0;
                        if(o.__size < pos)
                        {
                            throw exception();  // NOLINT
                        }
                        else
                        {
                            len = o.__size - pos;
                        }

                        if(len > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < len)
                                {
                                    __capacity = ((__size + (len - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                                    __size += (len - n);
                                    __data[__size] = 0;
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                                    __size -= (n - len);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, o, pos);
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o, pos);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & replace(type::size offset, type::size n, const string & o, type::size pos, type::size len)
                {
                    if(offset < __size)
                    {
                        if(o.__size < pos)
                        {
                            throw exception();  // NOLINT
                        }
                        else
                        {
                            len = (o.__size - pos < len ? o.__size - pos : len);
                        }
                        if(len > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < len)
                                {
                                    __capacity = ((__size + (len - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                                    __size += (len - n);
                                    __data[__size] = 0;
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], &o.__data[pos], len);
                                    __size -= (n - len);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, o, pos, len);
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o, pos, len);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & replace(type::size offset, type::size n, string && o)
                {
                    if(offset < __size)
                    {
                        if(o.__size > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < o.__size)
                                {
                                    __capacity = ((__size + (o.__size - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                                    __size += (o.__size - n);
                                    __data[__size] = 0;
                                }
                                else if(n ==  o.__size)
                                {
                                    memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], o.__data, o.__size);
                                    __size -= (n - o.__size);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, move(o));
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(o);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & replace(type::size offset, type::size n, const char * s)
                {
                    if(offset < __size)
                    {
                        type::size len = (s != nullptr ? string::length(s) : 0);
                        if(len > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < len)
                                {
                                    __capacity = ((__size + (len - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], s, len);
                                    __size += (len - n);
                                    __data[__size] = 0;
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::character>(&__data[offset], s, len);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], s, len);
                                    __size -= (n - len);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, s, len);
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(s);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & replace(type::size offset, type::size n, const char * s, type::size len)
                {
                    if(offset < __size)
                    {
                        if(s == nullptr && len > 0)
                        {
                            throw exception();  // NOLINT
                        }
                        if(len > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < len)
                                {
                                    __capacity = ((__size + (len - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], s, len);
                                    __size += (len - n);
                                    __data[__size] = 0;
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::character>(&__data[offset], s, len);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::character>(&__data[offset], s, len);
                                    __size -= (n - len);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, s, len);
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(s, len);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & replace(type::size offset, type::size n, type::character c)
                {
                    if(offset < __size)
                    {
                        n = __size - offset < n ? __size - offset : n;
                        if(n > 0)
                        {
                            if(n == 1)
                            {
                                __data[offset] = c;
                            }
                            else
                            {
                                memory::move<type::character>(&__data[offset + 1], &__data[offset + n], __size - offset - n);
                                __data[offset] = c;
                                __size -= (n - 1);
                                __data[__size] = 0;
                            }
                        }
                        else
                        {
                            insert(offset, c);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(c);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }

    public:     string & replace(type::size offset, type::size n, type::character c, type::size len)
                {
                    if(offset < __size)
                    {
                        if(len > 0)
                        {
                            n = __size - offset < n ? __size - offset : n;
                            if(n > 0)
                            {
                                if(n < len)
                                {
                                    __capacity = ((__size + (len - n)) / page + 1) * page;
                                    __data = memory::allocate<type::character>(__data, __capacity);
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::fill<type::character>(&__data[offset], c, len);
                                    __size += (len - n);
                                    __data[__size] = 0;
                                }
                                else if(n == len)
                                {
                                    memory::fill<type::character>(&__data[offset], c, len);
                                }
                                else
                                {
                                    memory::move<type::character>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::fill<type::character>(&__data[offset], c, len);
                                    __size -= (n - len);
                                    __data[__size] = 0;
                                }
                            }
                            else
                            {
                                insert(offset, c, len);
                            }
                        }
                        else if(n > 0)
                        {
                            erase(offset, n);
                        }
                    }
                    else if(offset == __size)
                    {
                        append(c, len);
                    }
                    else
                    {
                        throw exception();  // NOLINT
                    }
                    return *this;
                }
    public:     string & clear()
                {
                    __size = 0;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__data, __capacity);
                    __data[__size] = 0;
                    return *this;
                }
    public:     type::character & at(type::size i)
                {
                    if(__size <= i)
                    {
                        throw exception();  // NOLINT
                    }
                    return __data[i];
                }
    public:     const type::character & at(type::size i) const
                {
                    if(__size <= i)
                    {
                        throw exception();  // NOLINT
                    }
                    return __data[i];
                }
    public:     type::character & operator[](type::size i)
                {
                    return at(i);
                }
    public:     const type::character & operator[](type::size i) const
                {
                    return at(i);
                }
    public:     string & operator=(const string & o)
                {
                    return assign(o);   // NOLINT
                }
    public:     string & operator=(string && o) noexcept
                {
                    return assign(move(o));   // NOLINT
                }
    public:     string & operator=(const type::character * s)
                {
                    return assign(s);   // NOLINT
                }
    public:     string & operator=(type::character c)
                {
                    return assign(c);   // NOLINT
                }
    public:     string & operator+=(const string & o)
                {
                    return append(o);
                }
    public:     string & operator+=(string && o)
                {
                    return append(move(o));
                }
    public:     string & operator+=(const type::character * s)
                {
                    return append(s);
                }
    public:     string & operator+=(type::character c)
                {
                    return append(c);
                }
    public:     string() : __data(nullptr), __size(0), __capacity(0)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    __data[__size] = 0;
                }
    public:     string(const string & o) : __data(nullptr), __size(0), __capacity(0)
                {
                    __capacity = o.__capacity;
                    __size = o.__size;
                    __data = memory::allocate<type::character>(__capacity);
                    memory::copy<type::character>(__data, o.__data, __size);
                    __data[__size] = 0;
                }
    public:     string(const string & o, type::size position) : __data(nullptr), __size(0), __capacity(0)
                {
                    if(position < o.__size)
                    {
                        type::size length = o.__size - position;
                        __capacity = (length / page + 1) * page;
                        __data = memory::allocate<type::character>(__capacity);
                        memory::copy<type::character>(__data, &o.__data[position], length);
                        __size = length;
                        __data[__size] = 0;
                    }
                    else
                    {
                        if(o.__size < position)
                        {
                            WARNING_LOG("o.__size < position");
                        }
                        __capacity = (__size / page + 1) * page;
                        __data = memory::allocate<type::character>(__capacity);
                        __data[__size] = 0;
                    }
                }
    public:     string(const string & o, type::size position, type::size length) : __data(nullptr), __size(0), __capacity(0)
                {
                    if(position < o.__size)
                    {
                        if(o.__size - position < length)
                        {
                            NOTICE_LOG("o.__size - position < length");
                            length = o.__size - position;
                        }
                        __capacity = (length / page + 1) * page;
                        __data = memory::allocate<type::character>(__capacity);
                        memory::copy<type::character>(__data, &o.__data[position], length);
                        __size = length;
                        __data[__size] = 0;
                    }
                    else
                    {
                        if(o.__size < position)
                        {
                            WARNING_LOG("o.__size < position");
                        }
                        __capacity = (__size / page + 1) * page;
                        __data = memory::allocate<type::character>(__capacity);
                        __data[__size] = 0;
                    }
                }
    public:     string(string && o) noexcept : __data(o.__data), __size(o.__size), __capacity(o.__capacity)
                {
                    o.__data = nullptr;
                    o.__size = 0;
                    o.__capacity = 0;
                }
    public:     explicit string(const type::character * s) : __data(nullptr), __size(0), __capacity(0)
                {
                    type::size length = string::length(s);
                    __size = length;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    if(__size > 0)
                    {
                        memory::copy<type::character>(__data, s, __size);
                    }
                    __data[__size] = 0;
                }
    public:     string(const type::character * s, type::size length) : __data(nullptr), __size(0), __capacity(0)
                {
                    if(s == nullptr)
                    {
                        WARNING_LOG("s == nullptr");
                        length = 0;
                    }
                    __size = length;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    if(__size > 0)
                    {
                        memory::copy<type::character>(__data, s, __size);
                    }
                    __data[__size] = 0;
                }
    public:     explicit string(type::character c) : __data(nullptr), __size(1), __capacity(0)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    __data[0] = c;
                    __data[__size] = 0;
                }
    public:     string(type::character c, type::size length) : __data(nullptr), __size(length), __capacity(0)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::character>(__capacity);
                    if(length > 0)
                    {
                        memory::set(__data, c, length);
                    }

                    __data[__size] = 0;
                }
    public:     virtual ~string()
                {
                    __data = memory::deallocate<type::character>(__data);
                    __size = 0;
                    __capacity = 0;
                }
    };

    inline bool operator==(const string & x, const string & y) noexcept
    {
        return string::equal(x, y);
    }
    inline bool operator==(const char *   x, const string & y)
    {
        return string::equal(x, y);
    }
    inline bool operator==(const string & x, const char *   y)
    {
        return string::equal(x, y);
    }

    inline bool operator!=(const string & x, const string & y) noexcept
    {
        return string::different(x, y);
    }
    inline bool operator!=(const char *   x, const string & y)
    {
        return string::different(x, y);
    }
    inline bool operator!=(const string & x, const char *   y)
    {
        return string::different(x, y);
    }

    inline bool operator< (const string & x, const string & y) noexcept
    {
        return string::compare(x, y) < 0;
    }
    inline bool operator< (const char *   x, const string & y)
    {
        return string::compare(x, y) < 0;
    }
    inline bool operator< (const string & x, const char *   y)
    {
        return string::compare(x, y) < 0;
    }
    inline bool operator<=(const string & x, const string & y) noexcept
    {
        return string::compare(x, y) <= 0;
    }
    inline bool operator<=(const char *   x, const string & y)
    {
        return string::compare(x, y) <= 0;
    }
    inline bool operator<=(const string & x, const char *   y)
    {
        return string::compare(x, y) <= 0;
    }
    inline bool operator> (const string & x, const string & y) noexcept
    {
        return string::compare(x, y) > 0;
    }
    inline bool operator> (const char *   x, const string & y)
    {
        return string::compare(x, y) > 0;
    }
    inline bool operator> (const string & x, const char *   y)
    {
        return string::compare(x, y) > 0;
    }
    inline bool operator>=(const string & x, const string & y) noexcept
    {
        return string::compare(x, y) >= 0;
    }
    inline bool operator>=(const char *   x, const string & y)
    {
        return string::compare(x, y) >= 0;
    }
    inline bool operator>=(const string & x, const char *   y)
    {
        return string::compare(x, y) >= 0;
    }
}

#endif // __NOVEMBERIZING__STRING__HH__
