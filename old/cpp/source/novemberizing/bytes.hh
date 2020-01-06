/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 17.
 */

#ifndef   __NOVEMBERIZING___BYTES__HH__
#define   __NOVEMBERIZING___BYTES__HH__

#include <novemberizing.hh>
#include <novemberizing/exception.hh>
#include <novemberizing/memory.hh>

namespace novemberizing
{
    class bytes
    {
    public:     static const type::size page = 64;
    protected:  type::size __capacity;
    protected:  type::size __size;
    protected:  type::byte * __data;
    public:     type::size capacity() const { return __capacity; }
    public:     type::size size() const { return __size; }
    public:     const type::byte * v(type::size i) const
                {
                    if(__capacity <= i)
                    {
                        throw exception();  // NOLINT
                    }
                    return &__data[i];
                }
    public:     const type::byte * v() const
                {
                    return __data;
                }
    public:     type::byte & at(type::size i)
                {
                    if(__size <= i)
                    {
                        throw exception();  // NOLINT
                    }
                    return __data[i];
                }
    public:     const type::byte & at(type::size i) const
                {
                    if(__size <= i)
                    {
                        throw exception();  // NOLINT
                    }
                    return __data[i];
                }
    public:     bytes & assign(const bytes & o)
                {
                    if(&o != this)
                    {
                        __size = o.__size;
                        __capacity = o.__capacity;
                        __data = memory::allocate<type::byte>(__data, __size);
                        memory::copy<type::byte>(__data, o.__data, __size);
                    }
                    return *this;
                }
    public:     bytes & assign(const bytes & o, type::size pos)
                {
                    if(&o != this)
                    {
                        if(o.__size < pos)
                        {
                            throw exception();  // NOLINT
                        }
                        __size = o.__size - pos;
                        __capacity = (__size / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __size);
                        memory::copy<type::byte>(__data, &o.__data[pos], __size);
                    }
                    return *this;
                }
    public:     bytes & assign(const bytes & o, type::size pos, type::size len)
                {
                    if(&o != this)
                    {
                        if(o.__size < pos)
                        {
                            throw exception();  // NOLINT
                        }
                        __size = (o.__size - pos < len ? o.__size - pos : len);
                        __capacity = (__size / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __size);
                        memory::copy<type::byte>(__data, &o.__data[pos], __size);
                    }
                    return *this;
                }
    public:     bytes & assign(bytes && o) noexcept
                {
                    if(&o != this)
                    {
                        __capacity = o.__capacity;
                        __size = o.__size;
                        __data = o.__data;

                        o.__capacity = 0;
                        o.__size = 0;
                        o.__data = nullptr;
                    }
                    return *this;
                }
    public:     bytes & assign(const type::byte * s, type::size len)
                {
                    __size = len;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::copy<type::byte>(__data, s, len);
                    return *this;
                }
    public:     bytes & assign(type::byte c)
                {
                    __size = 1;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    __data[0] = c;
                    return *this;
                }
    public:     bytes & assign(type::byte c, type::size len)
                {
                    __size = len;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::fill<type::byte>(__data, c, __size);
                    return *this;
                }
    public:     bytes & append(const bytes & o)
                {
                    if(&o == this)
                    {
                        throw exception();  // NOLINT
                    }
                    __capacity = ((__size + o.__size) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::copy<type::byte>(&__data[__size], o.__data, o.__size);
                    __size += o.__size;
                    return *this;
                }
    public:     bytes & append(const bytes & o, type::size pos)
                {
                    if(&o == this)
                    {
                        throw exception();  // NOLINT
                    }
                    if(o.__size < pos)
                    {
                        throw exception();  // NOLINT
                    }
                    __capacity = ((__size + o.__size - pos) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::copy<type::byte>(&__data[__size], &o.__data[pos], o.__size - pos);
                    __size += (o.__size - pos);
                    return *this;
                }
    public:     bytes & append(const bytes & o, type::size pos, type::size len)
                {
                    if(&o == this)
                    {
                        throw exception();  // NOLINT
                    }
                    if(o.__size < pos)
                    {
                        throw exception();  // NOLINT
                    }
                    len = o.__size - pos < len ? o.__size - pos : len;
                    __capacity = ((__size + len) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::copy<type::byte>(&__data[__size], &o.__data[pos], len);
                    __size += len;
                    return *this;
                }
    public:     bytes & append(bytes && o)
                {
                    if(&o == this)
                    {
                        throw exception();  // NOLINT
                    }
                    __capacity = ((__size + o.__size) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::copy<type::byte>(&__data[__size], o.__data, o.__size);
                    __size += o.__size;
                    return *this;
                }
    public:     bytes & append(const type::byte * s, type::size len)
                {
                    if(s == nullptr && len > 0)
                    {
                        throw exception();  // NOLINT
                    }
                    __capacity = ((__size + len) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::copy<type::byte>(&__data[__size], s, len);
                    __size += len;
                    return *this;
                }
    public:     bytes & append(type::byte c)
                {
                    __capacity = ((__size + 1) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    __data[__size] = c;
                    __size += 1;
                    return *this;
                }
    public:     bytes & append(type::byte c, type::size len)
                {
                    __capacity = ((__size + len) / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    memory::fill<type::byte>(&__data[__size], c, len);
                    __size += len;
                    return *this;
                }
    public:     bytes & insert(type::size offset, const bytes & o)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    if(&o == this)
                    {
                        throw exception();  // NOLINT
                    }
                    if(offset < __size)
                    {
                        __capacity = ((__size + o.__size) / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __capacity);
                        memory::move<type::byte>(&__data[offset + o.__size] , &__data[offset], __size - offset);
                        memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                        __size += o.__size;
                    }
                    else
                    {
                        return append(o);
                    }
                    return *this;
                }
    public:     bytes & insert(type::size offset, const bytes & o, type::size pos)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    else
                    {
                        if(offset < __size)
                        {
                            if(&o == this)
                            {
                                throw exception();  // NOLINT
                            }
                            if(o.__size < pos)
                            {
                                throw exception();  // NOLINT
                            }
                            __capacity = ((__size + o.__size - pos) / page + 1) * page;
                            __data = memory::allocate<type::byte>(__data, __capacity);
                            memory::move<type::byte>(&__data[offset + o.__size - pos] , &__data[offset], __size - offset);
                            memory::copy<type::byte>(&__data[offset], o.__data, o.__size - pos);
                            __size += (o.__size  - pos);
                        }
                        else
                        {
                            return append(o, pos);
                        }
                    }
                    return *this;
                }
    public:     bytes & insert(type::size offset, const bytes & o, type::size pos, type::size len)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    else
                    {
                        if(offset < __size)
                        {
                            if(&o == this)
                            {
                                throw exception();  // NOLINT
                            }
                            if(o.__size < pos)
                            {
                                throw exception();  // NOLINT
                            }
                            len = (o.__size - pos < len ? o.__size - pos : len);
                            __capacity = ((__size + len) / page + 1) * page;
                            __data = memory::allocate<type::byte>(__data, __capacity);
                            memory::move<type::byte>(&__data[offset + len] , &__data[offset], __size - offset);
                            memory::copy<type::byte>(&__data[offset], o.__data, len);
                            __size += len;
                        }
                        else
                        {
                            return append(o, pos, len);
                        }
                    }
                    return *this;
                }
    public:     bytes & insert(type::size offset, bytes && o)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    if(&o == this)
                    {
                        throw exception();  // NOLINT
                    }
                    if(offset < __size)
                    {
                        __capacity = ((__size + o.__size) / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __capacity);
                        memory::move<type::byte>(&__data[offset + o.__size] , &__data[offset], __size - offset);
                        memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                        __size += o.__size;
                    }
                    else
                    {
                        return append(o);
                    }
                    return *this;
                }
    public:     bytes & insert(type::size offset, const type::byte * s, type::size len)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    if(offset < __size)
                    {
                        if(s == nullptr && len > 0)
                        {
                            throw exception();  // NOLINT
                        }
                        __capacity = ((__size + len) / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __capacity);
                        memory::move<type::byte>(&__data[offset + len] , &__data[offset], __size - offset);
                        memory::copy<type::byte>(&__data[offset], s, len);
                        __size += len;
                    }
                    else
                    {
                        return append(s, len);
                    }
                    return *this;
                }
    public:     bytes & insert(type::size offset, type::byte c)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    if(offset < __size)
                    {
                        __capacity = ((__size + 1) / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __capacity);
                        memory::move<type::byte>(&__data[offset + 1] , &__data[offset], __size - offset);
                        __data[offset] = 1;
                        __size += 1;
                    }
                    else
                    {
                        return append(c);
                    }
                    return *this;
                }
    public:     bytes & insert(type::size offset, type::byte c, type::size len)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    if(offset < __size)
                    {
                        __capacity = ((__size + len) / page + 1) * page;
                        __data = memory::allocate<type::byte>(__data, __capacity);
                        memory::move<type::byte>(&__data[offset + len], &__data[offset], __size - offset);
                        memory::fill<type::byte>(&__data[offset], c, len);
                        __size += len;
                    }
                    else
                    {
                        return append(c, len);
                    }
                    return *this;
                }
    public:     bytes & replace(type::size offset, type::size n, const bytes & o)
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
                                    __data = memory::allocate<type::byte>(__data, __capacity);
                                    memory::move<type::byte>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                                    __size += (o.__size - n);
                                }
                                else if(n ==  o.__size)
                                {
                                    memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                                }
                                else
                                {
                                    memory::move<type::byte>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                                    __size -= (n - o.__size);
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
                        throw exception(); // NOLINT
                    }
                    return *this;
                }
    public:     bytes & replace(type::size offset, type::size n, const bytes & o, type::size pos)
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
                                    __data = memory::allocate<type::byte>(__data, __capacity);
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], &o.__data[pos], len);
                                    __size += (len - n);
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::byte>(&__data[offset], &o.__data[pos], len);
                                }
                                else
                                {
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], &o.__data[pos], len);
                                    __size -= (n - len);
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
    public:     bytes & replace(type::size offset, type::size n, const bytes & o, type::size pos, type::size len)
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
                                    __capacity = ((__size + (len - n)) / page + 1) * page; // capacity::get(__size + (len - n), bytes::page);
                                    __data = memory::allocate<type::byte>(__data, __capacity);
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], &o.__data[pos], len);
                                    __size += (len - n);
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::byte>(&__data[offset], &o.__data[pos], len);
                                }
                                else
                                {
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], &o.__data[pos], len);
                                    __size -= (n - len);
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
    public:     bytes & replace(type::size offset, type::size n, bytes && o)
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
                                    __data = memory::allocate<type::byte>(__data, __capacity);
                                    memory::move<type::byte>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                                    __size += (o.__size - n);
                                    __data[__size] = 0;
                                }
                                else if(n ==  o.__size)
                                {
                                    memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
                                }
                                else
                                {
                                    memory::move<type::byte>(&__data[offset + o.__size], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], o.__data, o.__size);
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
    public:     bytes & replace(type::size offset, type::size n, const type::byte * s, type::size len)
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
                                    __data = memory::allocate<type::byte>(__data, __capacity);
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], s, len);
                                    __size += (len - n);
                                }
                                else if(n == len)
                                {
                                    memory::copy<type::byte>(&__data[offset], s, len);
                                }
                                else
                                {
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::copy<type::byte>(&__data[offset], s, len);
                                    __size -= (n - len);
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
    public:     bytes & replace(type::size offset, type::size n, type::byte c)
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
                                memory::move<type::byte>(&__data[offset + 1], &__data[offset + n], __size - offset - n);
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
    public:     bytes & replace(type::size offset, type::size n, type::byte c, type::size len)
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
                                    __data = memory::allocate<type::byte>(__data, __capacity);
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::fill<type::byte>(&__data[offset], c, len);
                                    __size += (len - n);
                                }
                                else if(n == len)
                                {
                                    memory::fill<type::byte>(&__data[offset], c, len);
                                }
                                else
                                {
                                    memory::move<type::byte>(&__data[offset + len], &__data[offset + n], __size - offset - n);
                                    memory::fill<type::byte>(&__data[offset], c, len);
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
    public:     bytes & erase()
                {
                    __size = 0;
                    return *this;
                }
    public:     bytes & erase(type::size offset)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    __size = offset;
                    return *this;
                }
    public:     bytes & erase(type::size offset, type::size n)
                {
                    if(__size < offset)
                    {
                        throw exception();  // NOLINT
                    }
                    n = __size - offset < n ? __size - offset : n;
                    if(offset + n < __size)
                    {
                        memory::move<type::byte>(&__data[offset], &__data[offset + n], __size - offset - n);
                        __size -= n;
                    }
                    else
                    {
                        __size = offset;
                    }
                    return *this;
                }
    public:     bytes & clear()
                {
                    __size = 0;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__data, __capacity);
                    return *this;
                }
    public:     bytes & operator=(const bytes & o)
                {
                    return assign(o);   // NOLINT
                }
    public:     bytes & operator=(bytes && o) noexcept
                {
                    return assign(move(o));   // NOLINT
                }
    public:     bytes & operator=(type::byte c)
                {
                    return assign(c);   // NOLINT
                }
    public:     bytes & operator+=(const bytes & o)
                {
                    return append(o);
                }
    public:     bytes & operator+=(bytes && o)
                {
                    return append(move(o));
                }
    public:     bytes & operator+=(type::byte c)
                {
                    return append(c);
                }
    public:     type::byte & operator[](type::size i)
                {
                    return at(i);
                }
    public:     const type::byte & operator[](type::size i) const
                {
                    return at(i);
                }
    public:     explicit bytes(type::int16 n) : __capacity(0), __size(sizeof(type::int16)), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, (type::byte *) &n, sizeof(type::int16));
                }
    public:     explicit bytes(type::int32 n) : __capacity(0), __size(sizeof(type::int32)), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, (type::byte *) &n, sizeof(type::int32));
                }
    public:     explicit bytes(type::int64 n) : __capacity(0), __size(sizeof(type::int64)), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, (type::byte *) &n, sizeof(type::int64));
                }
    public:     explicit bytes(type::uint16 n) : __capacity(0), __size(sizeof(type::uint16)), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, (type::byte *) &n, sizeof(type::uint16));
                }
    public:     explicit bytes(type::uint32 n) : __capacity(0), __size(sizeof(type::uint32)), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, (type::byte *) &n, sizeof(type::uint32));
                }
    public:     explicit bytes(type::uint64 n) : __capacity(0), __size(sizeof(type::uint64)), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, (type::byte *) &n, sizeof(type::uint64));
                }
    public:     bytes() : __capacity(0), __size(0), __data(nullptr)
                {
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                }
    public:     bytes(const bytes & o) : __capacity(o.__capacity), __size(o.__size), __data(nullptr)
                {
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, o.__data, __size);
                }
    public:     bytes(const bytes & o, type::size pos): __capacity(0), __size(0), __data(nullptr)
                {
                    if(o.__size < pos)
                    {
                        /** exception handling */
                        __size = 0;
                    }
                    else
                    {
                        __size = o.__size - pos;
                    }
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, &o.__data[pos], __size);
                }
    public:     bytes(const bytes & o, type::size pos, type::size len) : __capacity(0), __size(0), __data(nullptr)
                {
                    if(o.__size < pos)
                    {
                        /** exception handling */
                        __size = 0;
                    }
                    else
                    {

                        __size = (o.__size - pos < len ? o.__size - pos : len);
                    }
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::copy<type::byte>(__data, &o.__data[pos], __size);
                }
    public:     bytes(bytes && o) noexcept : __capacity(o.__capacity), __size(o.__size), __data(o.__data)
                {
                    o.__capacity = 0;
                    o.__size = 0;
                    o.__data = nullptr;
                }
    public:     bytes(const type::byte * s, type::size len) : __capacity(0), __size(0), __data(nullptr)
                {
                    if(s != nullptr && len > 0)
                    {
                        __size = len;
                        __capacity = (__size / page + 1) * page;
                        __data = memory::allocate<type::byte>(__capacity);
                        memory::copy<type::byte>(__data, s, __size);
                    }
                    else
                    {
                        __capacity = (__size / page + 1) * page;
                        __data = memory::allocate<type::byte>(__capacity);
                    }
                }
    public:     explicit bytes(type::byte c) : __capacity(0), __size(0), __data(nullptr)
                {
                    __size = 1;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    __data[0] = c;
                }

    public:     bytes(type::byte c, type::size len) : __capacity(0), __size(0), __data(nullptr)
                {
                    __size = len;
                    __capacity = (__size / page + 1) * page;
                    __data = memory::allocate<type::byte>(__capacity);
                    memory::fill<type::byte>(__data, c, __size);
                }
    public:     virtual ~bytes()
                {
                    __size = 0;
                    __capacity = 0;
                    __data = memory::deallocate<type::byte>(__data);
                }
    };
}

#endif // __NOVEMBERIZING___BYTES__HH__
