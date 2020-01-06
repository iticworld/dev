#ifndef   __NOVEMBERIZING_IO_BUFFERS__CONTINUOUS__INLINE__HH__
#define   __NOVEMBERIZING_IO_BUFFERS__CONTINUOUS__INLINE__HH__

#include <novemberizing/io/buffers/continuous.hh>

namespace novemberizing { namespace io { namespace buffers {

/**
 * @fn          inline continuous::continuous(void)
 * @brief       default constructor of ds::buffers::continuous
 * @details
 */
inline Continuous::Continuous(void)
{
    __page = 0;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;
}

/**
 * @fn          inline continuous::continuous(type::size page)
 * @brief       constructor of ds::buffers::continuous to initialize with page.
 * @details
 * @param [in]  | page | type::size | - | ... |
 */
inline Continuous::Continuous(type::size page)
{
    __page = page;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;

    capacity(page);
}

/**
 * @fn          inline continuous::continuous(const ds::buffers::continuous & x)
 * @brief       constructor of ds::buffers::continuous to copy from the other object
 * @details
 * @param [in]  | x | ds::buffers::continuous & | - | ... |
 */
inline Continuous::Continuous(const Continuous & x)
{
    __page = x.page();
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;


    assign(x,0,x.size());
}

/**
 * @fn          inline continuous::continuous(const type::character * str,type::size position,type::size length,type::size page)
 * @brief       constructor of ds::buffers::continuous to initialize from string.
 * @details
 * @param [in]  | str | const type::character * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @param [in]  | page | type::size | 0 | ... |
 */
inline Continuous::Continuous(const char * str,type::size position,type::size length,type::size page)
{
    __page = page;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;

    assign(str,position,length);
}

/**
 * @fn          inline continuous::continuous(const type::byte * bytes,type::size position,type::size length,type::size page)
 * @brief       constructor of ds::buffers::continuous to initialize from byte array.
 * @details
 * @param [in]  | bytes | const type::byte * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @param [in]  | page | type::size | 0 | ... |
 */
inline Continuous::Continuous(const type::byte * bytes,type::size position,type::size length,type::size page)
{
    __page = page;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;

    assign(bytes,position,length);
}

/**
* @fn          inline continuous::continuous(const ds::buffer & bytes,type::size position,type::size length,type::size page)
* @brief       constructor of ds::buffers::continuous to initialize from the other buffer.
* @details
* @param [in]  | bytes | const ds::buffer & | - | ... |
* @param [in]  | position | type::size | 0 | ... |
* @param [in]  | length | type::size | constant::eop | ... |
* @param [in]  | page | type::size | 0 | ... |
 */
inline Continuous::Continuous(const Buffer & buf,type::size position,type::size length,type::size page)
{
    __page = page;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;

    assign(buf,position,length);
}

/**
 * @fn          inline continuous::continuous(type::byte byte,type::size length,type::size page)
 * @brief       constructor of ds::buffers::continuous to initialize to fill byte.
 * @details
 * @param [in]  | byte | type::byte | - | ... |
 * @param [in]  | length | type::size | - | ... |
 * @param [in]  | page | type::size | 0 | ... |
 */
inline Continuous::Continuous(type::byte byte,type::size length,type::size page)
{
    __page = page;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;

    assign(byte,length);
}

/**
 * @fn          inline continuous::continuous(type::character character,type::size length,type::size page)
 * @brief       constructor of ds::buffers::continuous to initialize to fill character.
 * @details
 * @param [in]  | character | type::character | - | ... |
 * @param [in]  | length | type::size | - | ... |
 * @param [in]  | page | type::size | 0 | ... |
 */
inline Continuous::Continuous(char character,type::size length,type::size page)
{
    __page = page;
    __bytes = nullptr;
    __size = 0;
    __capacity = 0;

    assign(character,length);
}

inline Continuous::~Continuous(void)
{
    if(__bytes!=nullptr)
    {
        ::free(__bytes);
        __bytes = nullptr;
    }

    __size = 0;
    __capacity = 0;
    __size = 0;
}

/**
 * @fn          inline type::size continuous::capacity(void) const
 * @brief       get capacity
 * @details
 * @return      | type::size | ... |
 */
inline type::size Continuous::capacity(void) const
{
    return __capacity;
}

/**
 * @fn          inline type::size continuous::size(void) const
 * @brief       get allocated and setted size
 * @details
 * @return      | type::size | ... |
 */
inline type::size Continuous::size(void) const
{
    return __size;
}

/**
 * @fn          inline void continuous::capacity(type::size value)
 * @brief       set capacity
 * @details
 * @param [in]  | value | type::size | - | ... |
 */
inline void Continuous::capacity(type::size value)
{
    //FUNCTION_START();
    /** apply with page */
    value = __page==0 ? value : value!=0 ? ((value/__page + (value%__page==0 ? 0 : 1)) * __page) : __page;
    if(__capacity!=value)
    {
        if(value>0)
        {
            __bytes = (type::byte *) ::realloc(__bytes,value);
            if(value < __size){ __size = value; }
            __capacity = value;
        }
        else
        {
            ::free(__bytes);
            __bytes = nullptr;
            __size = 0;
            __capacity = value;
        }
    }
    //FUNCTION_END();
}

/**
 * @fn          inline void continuous::resize(type::size value,int c)
 * @brief       resize buffer
 * @details
 * @param [in]  | size | type::size | - | ... |
 * @param [in]  | c | int | 0 | ... |
 */
inline void Continuous::resize(type::size value,int c)
{
    if(value<__capacity)
    {
        for(type::size i = __size;i<value;i++)
        {
            __bytes[i] = c;
        }
        __size = value;
        capacity(__size);
    }
    else
    {
        capacity(value);
        for(type::size i = __size;i<value;i++)
        {
            __bytes[i] = c;
        }
        __size = value;
    }
}

/**
 * @fn          inline int continuous::erase(type::size offset,type::size n)
 * @brief       erase buffer
 * @details
 * @param [in]  | offset | type::size | 0 | ... |
 * @param [in]  | n | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::erase(type::size offset,type::size n)
{
    /** adjust buffer offset */
    if(__size < offset){ offset = __size; }
    /** adjust buffer n */
    n = __size - offset < n ? __size - offset : n;
    /** adjust buffer n */
    if(offset + n == __size)
    {
        __size = offset;
        capacity(__size);
    }
    else
    {
        ::memmove(&__bytes[offset],&__bytes[offset + n],__size - (offset + n));
        __size -= n;
        capacity(__size);
    }
    return Success;
}

/**
 * @fn          inline void cont0inuous::clear(void)
 * @brief       clear buffer
 * @details
 */
inline void Continuous::clear(void)
{
    __size = 0;
    capacity(__size);
}

/**
 * @fn          inline type::byte & continuous::at(type::size index)
 * @brief       get character at the position
 * @details
 * @param [in]  | index | type::size | - | ... |
 * @return      | char & | ... |
 */
inline type::byte & Continuous::at(type::size index)
{
    // if(__size<=index){ throw Throwable("__size<=index"); }
    return __bytes[index];
}

/**
 * @fn          inline const type::byte & continuous::at(type::size index) const
 * @brief       get character reference at the position
 * @details
 * @param [in]  | index | type::size | - | ... |
 * @return      | const char & | ... |
 */
inline const type::byte & Continuous::at(type::size index) const
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    return __bytes[index];
}

/**
 * @fn          inline type::byte & continuous::operator[](type::size index)
 * @brief       get character reference at the position
 * @details
 * @param [in]  | index | type::size | - | ... |
 * @return      | char & | ... |
 */
inline type::byte & Continuous::operator[](type::size index)
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    return __bytes[index];
}

/**
 * @fn          inline const type::byte & continuous::operator[](type::size index) const
 * @brief       get character reference at the position
 * @details
 * @param [in]  | index | type::size | - | ... |
 * @return      | const char & | ... |
 */
inline const type::byte & Continuous::operator[](type::size index) const
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    return __bytes[index];
}

/**
 * @fn          inline type::size continuous::copy(type::byte * out,type::size position,type::size length)
 * @brief       copy to byte array.
 * @details
 * @param [in]  | out | type::byte * | - | ... |
 * @param [in]  | offset | type::size | 0 | ... |
 * @param [in]  | n | type::size | n | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::copy(type::byte * out,type::size offset,type::size n) const
{
    // if(out==nullptr){ EXCEPTION("out==nullptr"); }
    /** adjust offset parameter */
    if(__size < offset){ offset = __size; }
    /** adjust n parameter */
    n = __size - offset < n ? __size - offset : n;
    /** copy */
    ::memcpy(out,&__bytes[offset],n);
    return n;
}

/**
 * @fn          inline type::size continuous::copy(type::character * out,type::size position,type::size length)
 * @brief       copy to byte array.
 * @details
 * @param [in]  | out | type::character * | - | ... |
 * @param [in]  | offset | type::size | 0 | ... |
 * @param [in]  | n | type::size | n | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::copy(char * out,type::size offset,type::size n) const
{
    return copy((type::byte *) out,offset,n);
}

inline type::byte * Continuous::back(void)
{
    return remain()>0 ? &__bytes[__size] : nullptr;
}

inline const type::byte * Continuous::back(void) const
{
    return remain()>0 ? &__bytes[__size] : nullptr;
}

inline type::byte * Continuous::front(void)
{
    return __bytes;
}

inline const type::byte * Continuous::front(void) const
{
    return __bytes;
}

/**
 * @fn          inline const type::byte * continuous::front(void) const
 * @brief       get front memory space
 * @details
 * @return      | const char * | ... |
 */
inline const type::byte * Continuous::front(type::size & len) const
{
    if(__size>0){ len = __size; }
    return __bytes;
}

/**
 * @fn          inline type::byte * continuous::front(void)
 * @brief       get front memory space
 * @details
 * @return      | char * | ... |
 */
inline type::byte * Continuous::front(type::size & len)
{
    if(__size>0){ len = __size; }
    return __bytes;
}

/**
 * @fn          inline const type::byte * continuous::back(void) const
 * @brief       get back space, not allocated first offset
 * @details
 * @return      | const char * | ... |
 */
inline const type::byte * Continuous::back(type::size & len) const
{
    if(__capacity - __size>0){ len = __capacity - __size; }
    return __capacity - __size >0 ? &__bytes[__size] : nullptr;
}

/**
 * @fn          inline type::byte * continuous::back(void)
 * @brief       get back space
 * @details
 * @param [in]  | char * | ... |
 */
inline type::byte * Continuous::back(type::size & len)
{
    if(__capacity - __size>0){ len = __capacity - __size; }
    return __capacity - __size >0 ? &__bytes[__size] : nullptr;
}

/**
 * @fn          inline type::size continuous::remain(void)
 * @brief       get remain size
 * @details
 * @return      | type::size | ... |
 */
inline type::size Continuous::remain(void) const
{
    return __capacity - __size;
}

/**
 * @fn          inline int continuous::assign(const type::byte * bytes,type::size position,type::size length)
 * @brief       assign byte array
 * @details
 * @param [in]  | bytes | const type::bytes * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::assign(const type::byte * bytes,type::size position,type::size length)
{
    // if(bytes==nullptr){ EXCEPTION("bytes==nullptr"); }
    /** adjust position length */
    if(length==eop)
    {
        length = ::strlen((char *) bytes);
        position = length < position ? length : position;
        length -= position;
    }
    __size = 0;
    capacity(length);
    if(length>0)
    {
        ::memcpy(__bytes,&bytes[position],length);
    }
    __size = length;
    return Success;
}

/**
 * @fn          inline int continuous::assign(const type::character * str,type::size position,type::size length)
 * @brief       assign
 * @details
 * @param [in]  | str | const type::character * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::assign(const char * str,type::size position,type::size length)
{
    return assign((type::byte *) str,position,length);
}

/**
 * @fn          inline int continuous::assign(const ds::buffer & buf,type::size position,type::size length)
 * @brief       assign buffer
 * @details
 * @param [in]  | buf | const ds::buffer & | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::assign(const Buffer & buf,type::size position,type::size length)
{
    /** adjust position parameter */
    if(buf.size() < position) { position = buf.size(); }
    /** adjust length parameter */
    if(length==eop) { length = buf.size() - position; }

    __size = 0;
    capacity(length);
    if(length>0) { buf.copy(__bytes,position,length); }
    __size = length;

    return Success;
}

/**
 * @fn          inline int continuous::assign(type::byte byte,type::size length)
 * @brief       assign buffer
 * @details
 * @param [in]  | byte | type::byte | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::assign(type::byte byte,type::size length)
{
    __size = 0;
    capacity(length);
    if(length>0)
    {
        ::memset(__bytes,byte,length);
    }
    __size = length;

    return Success;
}

/**
 * @fn          inline int continuous::assign(type::character character,type::size length)
 * @brief       assign buffer
 * @details
 * @param [in]  | character | type::character | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::assign(char character,type::size length)
{
    return assign((type::byte) character,length);
}

/**
 * @fn          inline int continuous::append(const type::byte * bytes,type::size position,type::size length)
 * @brief       append buffer
 * @details
 * @param [in]  | bytes | const type::byte * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::append(const type::byte * bytes,type::size position,type::size length)
{
    // if(bytes==nullptr){ EXCEPTION("bytes==nullptr"); }
    /** adjust position length */
    if(length==eop)
    {
        length = ::strlen((char *) bytes);
        position = length < position ? length : position;
        length -= position;
    }
    capacity(__size + length);
    if(length>0)
    {
        ::memcpy(&__bytes[__size],&bytes[position],length);
    }
    __size += length;

    return Success;
}

/**
 * @fn          inline int continuous::append(const type::character * str,type::size position,type::size length)
 * @brief       append buffer
 * @details
 * @param [in]  | str | const type::character * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::append(const char * str,type::size position,type::size length)
{
    return append((type::byte *) str,position,length);
}

/**
 * @fn          inline int continuous::append(const ds::buffer & buf,type::size position,type::size length)
 * @brief       append buffer
 * @details
 * @param       | buf | const ds::buffer & | - | ... |
 * @param       | position | type::size | 0 | ... |
 * @param       | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::append(const Buffer & buf,type::size position,type::size length)
{
    /** adjust position parameter */
    if(buf.size() < position) { position = buf.size(); }
    /** adjust length parameter */
    if(length==eop) { length = buf.size() - position; }

    capacity(__size + length);
    if(length>0)
    {
        buf.copy(&__bytes[__size],position,length);
    }
    __size += length;

    return Success;
}

/**
 * @fn          inline int continuous::append(type::byte byte,type::size length)
 * @brief       append buffer
 * @details
 * @param [in]  | byte | type::byte | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::append(type::byte byte,type::size length)
{
    if(length>0)
    {
        capacity(__size + length);
        for(type::size i = 0;i<length;i++)
        {
            __bytes[__size + i] = byte;
        }
        __size += length;
    }
    return Success;
}

/**
 * @fn          inline int continuous::append(type::character character,type::size length)
 * @brief       append buffer
 * @details
 * @param [in]  | character | type::character | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::append(char character,type::size length)
{
    return append((type::byte) character,length);
}

/**
 * @fn          inline int continuous::insert(type::size offset,const type::byte * bytes,type::size position,type::size length)
 * @brief       insert buffer into the offset
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | bytes | const type::bytes * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant:eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::insert(type::size offset,const type::byte * bytes,type::size position,type::size length)
{
//    if(bytes==nullptr){ EXCEPTION("bytes==nullptr"); }
    /** adjust offset */
    if(__size < offset){ offset = __size; }
    /** adjust position & length */
    if(length==eop)
    {
        length = ::strlen((char *) bytes);
        position = length < position ? length : position;
        length -= position;
    }

    if(length > 0)
    {
        capacity(__size + length);
        if(offset<__size) { ::memmove(&__bytes[offset + length],&__bytes[offset],__size - offset); }
        ::memcpy(&__bytes[offset],&bytes[position],length);
        __size += length;
    }
    return Success;
}

/**
 * @fn          inline int continuous::insert(type::size offset,const type::character * str,type::size position,type::size length)
 * @brief       insert buffer into the offset
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | str | const type::character * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::insert(type::size offset,const char * str,type::size position,type::size length)
{
    return insert(offset,(type::byte *) str,position,length);
}

/**
 * @fn          inline int continuous::insert(type::size offset,const ds::buffer & buf,type::size position,type::size length)
 * @brief       insert buffer
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | buf | const ds::buffer & | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::insert(type::size offset,const Buffer & buf,type::size position,type::size length)
{
    /** adjust offset */
    if(__size < offset){ offset = __size; }

    /** adjust position parameter */
    if(buf.size() < position) { position = buf.size(); }
    /** adjust length parameter */
    if(length==eop) { length = buf.size() - position; }

    if(length > 0)
    {
        capacity(__size + length);
        if(offset<__size) { ::memmove(&__bytes[offset + length],&__bytes[offset],__size - offset); }
        buf.copy(&__bytes[offset],position,length);
        __size += length;
    }
    return Success;
}

/**
 * @fn          inline int continuous::insert(type::size offset,type::byte byte,type::size length)
 * @brief       insert
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | byte | type::byte | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::insert(type::size offset,type::byte byte,type::size length)
{
    /** adjust offset */
    if(__size < offset){ offset = __size; }

    if(length > 0)
    {
        capacity(__size + length);
        if(offset<__size) { ::memmove(&__bytes[offset + length],&__bytes[offset],__size - offset); }
        for(type::size i = 0;i<length;i++){ __bytes[offset + i] = byte; }
        __size += length;
    }
    return Success;
}

/**
 * @fn          inline int continuous::insert(type::size offset,type::character character,type::size length)
 * @brief       insert
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | character | type::character | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::insert(type::size offset,char character,type::size length)
{
    return insert(offset, (type::byte) character, length);
}

/**
 * @fn          inline int continuous::replace(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length);
 * @brief       replace
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | n | type::size | - | ... |
 * @param [in]  | bytes | const type::byte * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::replace(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length)
{
//    if(bytes==nullptr){ EXCEPTION("bytes==nullptr"); }
    /** adjust offset */
    if(__size < offset){ offset = __size; }
    /** ajdust n */
    n = __size - offset < n ? __size - offset : n;

    /** adjust position & length */
    if(length==eop)
    {
        length = ::strlen((char *) bytes);
        position = length < position ? length : position;
        length -= position;
    }

    if(length>0)
    {
        if(n<length)
        {
            /** increasse */
            capacity(__size + (length - n));
            if(n>0 && offset + n < __size) { ::memmove(&__bytes[offset+length],&__bytes[offset+n],__size - (offset + n)); }
            ::memcpy(&__bytes[offset],&bytes[position],length);
            __size += (length - n);
        }
        else if(n>length)
        {
            /** decrease */
            if(n>0 && offset + n < __size){ ::memmove(&__bytes[offset+length],&__bytes[offset+n],__size - (offset + n)); }
            ::memcpy(&__bytes[offset],&bytes[position],length);
            __size -= (n - length);
        }
        else
        {
            /** same */
            ::memcpy(&__bytes[offset],&bytes[position],n);
        }
    }
    else
    {
        erase(offset,n);
    }
    return Success;
}

/**
 * @fn          inline int continuous::replace(type::size offset,type::size n,const type::character * str,type::size position,type::size length)
 * @brief       replace
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | n | type::size | - | ... |
 * @param [in]  | str | const type::character * | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::replace(type::size offset,type::size n,const char * str,type::size position,type::size length)
{
    return replace(offset,n,(type::byte *) str,position,length);
}

/**
 * @fn          inline int continuous::replace(type::size offset,type::size n,const ds::buffer & buf,type::size position,type::size length)
 * @brief       replace
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | n | type::size | - | ... |
 * @param [in]  | buf | const ds::buffer & | - | ... |
 * @param [in]  | position | type::size | 0 | ... |
 * @param [in]  | length | type::size | constant::eop | ... |
 * @return      | int | ... |
 */
inline int Continuous::replace(type::size offset,type::size n,const Buffer & buf,type::size position,type::size length)
{
    /** adjust offset */
    if(__size < offset){ offset = __size; }
    /** ajdust n */
    n = __size - offset < n ? __size - offset : n;

    /** adjust position parameter */
    if(buf.size() < position) { position = buf.size(); }
    /** adjust length parameter */
    if(length==eop) { length = buf.size() - position; }

    if(length>0)
    {
        if(n<length)
        {
            /** increasse */
            capacity(__size + (length - n));
            if(n>0 && offset + n < __size) { ::memmove(&__bytes[offset+length],&__bytes[offset+n],__size - (offset + n)); }
            buf.copy(&__bytes[offset],position,length);
            __size += (length - n);
        }
        else if(n>length)
        {
            /** decrease */
            if(n>0 && offset + n < __size){ ::memmove(&__bytes[offset+length],&__bytes[offset+n],__size - (offset + n)); }
            buf.copy(&__bytes[offset],position,length);
            __size -= (n - length);
        }
        else
        {
            /** same */
            buf.copy(&__bytes[offset],position,length);
        }
    }
    else
    {
        erase(offset,n);
    }
    return Success;
}

/**
 * @fn          inline int continuous::replace(type::size offset,type::size n,type::byte byte,type::size length)
 * @brief       replace
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | n | type::size | - | ... |
 * @param [in]  | byte | type::byte | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::replace(type::size offset,type::size n,type::byte byte,type::size length)
{
    /** adjust offset */
    if(__size < offset){ offset = __size; }
    /** ajdust n */
    n = __size - offset < n ? __size - offset : n;

    if(length>0)
    {
        if(n<length)
        {
            /** increasse */
            capacity(__size + (length - n));
            if(n>0 && offset + n < __size) { ::memmove(&__bytes[offset+length],&__bytes[offset+n],__size - (offset + n)); }
            for(type::size i = 0;i<length;i++){ __bytes[i + __size] = byte; }
            __size += (length - n);
        }
        else if(n>length)
        {
            /** decrease */
            if(n>0 && offset + n < __size){ ::memmove(&__bytes[offset+length],&__bytes[offset+n],__size - (offset + n)); }
            for(type::size i = 0;i<length;i++){ __bytes[i + __size] = byte; }
            __size -= (n - length);
        }
        else
        {
            /** same */
            for(type::size i = 0;i<length;i++){ __bytes[i + __size] = byte; }
        }
    }
    else
    {
        erase(offset,n);
    }
    return Success;
}

/**
 * @fn          inline int continuous::replace(type::size offset,type::size n,type::character character,type::size length)
 * @brief       replace
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | n | type::size | - | ... |
 * @param [in]  | character | type::character | - | ... |
 * @param [in]  | length | type::size | 1 | ... |
 * @return      | int | ... |
 */
inline int Continuous::replace(type::size offset,type::size n,char character,type::size length)
{
    return replace(offset,n,(type::byte) character,length);
}

/**
 * @fn          inline type::size continuous::find(type::size offset,const type::byte * bytes,type::size position,type::size length,ds::buffer::direction direction,ds::buffer::match match)
 * @brief       find
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | bytes | const type::byte * | - | ... |
 * @param [in]  | position | type:size | - | ... |
 * @param [in]  | length | type::size | - | ... |
 * @param [in]  | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]  | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,const type::byte * bytes,type::size position,type::size length,Direction direction,Match match)
{
//    if(bytes==nullptr){ EXCEPTION("bytes==nullptr"); }
    if(direction==forward)
    {
        if(match==entire)
        {
            if(length<=__size && length>0)
            {
                for(type::size i = offset;i<__size - length + 1;i++)
                {
                    if(::memcmp(&__bytes[offset],&bytes[position],length)==0){ return i; }
                }
            }
        }
        else if(match==partial)
        {
            for(type::size i = offset;i<__size;i++)
            {
                for(type::size j = position;j<position + length;j++)
                {
                    if(__bytes[i]==bytes[j]){ return i; }
                }
            }
        }
        else
        {
            bool match = false;
            for(type::size i = offset;i<__size;i++)
            {
                match = false;
                for(type::size j = position;!(match = (__bytes[i]==bytes[j])) && j<position + length;j++){}
                if(!match){ return i; }
            }
        }
    }
    else
    {
        if(match==entire)
        {
            if(length<=__size && length>0)
            {
                /** adjust offset */
                offset = __size - length < offset ? __size - length : offset;
                for(type::size i = offset;i+1>0;i--)
                {
                    if(::memcmp(&__bytes[offset],&bytes[position],length)==0){ return i; }
                }
            }
        }
        else if(match==partial)
        {
            /** adjust offset */
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;i--)
            {
                for(type::size j = position;j<position + length;j++)
                {
                    if(__bytes[i]==bytes[j]){ return i; }
                }
            }
        }
        else
        {
            /** adjust offset */
            offset = offset < __size ? offset : __size - 1;
            bool match = false;
            for(type::size i = offset;i+1>0;i--)
            {
                match = false;
                for(type::size j = position;!(match = (__bytes[i]==bytes[j])) && j<position + length;j++){}
                if(!match){ return i; }
            }
        }
    }
    return eop;
}

/**
 * @fn          inline type::size continuous::find(type::size offset,const type::byte * bytes,ds::buffer::direction direction,ds::buffer::match match)
 * @brief       find
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | bytes | const type:byte * | - | ... |
 * @param [in]  | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]  | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,const type::byte * bytes,Direction direction,Match match)
{
    //if(bytes==nullptr){ EXCEPTION("bytes==nullptr"); }
    return find(offset,bytes,0,::strlen((char *) bytes),direction,match);
}

/**
 * @fn          inline type::size continuous::find(type::size offset,const type::character * str,ds::buffer::direction direction,ds::buffer::match match)
 * @brief       find
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | str | const type:character * | - | ... |
 * @param [in]  | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]  | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,const char * str,Direction direction,Match match)
{
    // if(str==nullptr){ EXCEPTION("bytes==nullptr"); }
    return find(offset,(type::byte*) str,0,::strlen(str),direction,match);
}

/**
 * @fn          inline type::size continuous::find(type::size offset,const type::character * str,type::size position,type::size length,ds::buffer::direction direction,ds::buffer::match match)
 * @brief       find
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | str | const type::character * | - | ... |
 * @param [in]  | position | type:size | - | ... |
 * @param [in]  | length | type::size | - | ... |
 * @param [in]  | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]  | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,const char * str,type::size position,type::size length,Direction direction,Match match)
{
    // if(str==nullptr){ EXCEPTION("bytes==nullptr"); }
    return find(offset,(type::byte*) str,position,length,direction,match);
}

/**
 * @fn          inline type::size continuous::find(type::size offset,type::byte byte,ds::buffer::dirction direction,ds::buffer::match match)
 * @brief       find
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | byte | type::byte | - | ... |
 * @param [in]  | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]  | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,type::byte byte,Direction direction,Match match)
{
    if(direction==forward)
    {
        if(match==without)
        {
            for(type::size i = offset;i<__size;i++)
            {
                if(__bytes[i]!=byte) { return i; }
            }
        }
        else
        {
            for(type::size i = offset;i<__size;i++)
            {
                if(__bytes[i]==byte) { return i; }
            }
        }
    }
    else
    {
        offset = offset < __size ? offset : __size - 1;
        if(match==without)
        {
            for(type::size i = offset;i+1>0;i--)
            {
                if(byte!=__bytes[i]) { return i; }
            }
        }
        else
        {
            for(type::size i = offset;i+1>0;i--)
            {
                if(byte==__bytes[i]) { return i; }
            }
        }
    }
    return eop;
}

/**
 * @fn          inline type::size continuous::find(type::size offset,type::character character,ds::buffer::dirction direction,ds::buffer::match match)
 * @brief       find
 * @details
 * @param [in]  | offset | type::size | - | ... |
 * @param [in]  | character | type::character | - | ... |
 * @param [in]  | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]  | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return      | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,char character,Direction direction,Match match)
{
    return find(offset,(type::byte) character,direction,match);
}

/**
 * @fn              inline type::size continuous::find(type::size offset,const ds::buffer & buf,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return          | type::size | ... |
 */
inline type::size Continuous::find(type::size offset,const Buffer & buf,Direction direction,Match match)
{
    if(direction==forward)
    {
        if(match==entire)
        {
            if(buf.size()<=__size && buf.size()>0)
            {
                for(type::size i = offset;i<__size - buf.size() + 1;i++)
                {
                    if(buf.compare(&__bytes[offset],i,buf.size())==0) { return i; }
                }
            }
        }
        else if(match==partial)
        {
            for(type::size i = offset;i<__size;i++)
            {
                for(type::size j = 0;j<buf.size();j++)
                {
                    if(__bytes[i]==buf[j]) { return i; }
                }
            }
        }
        else
        {
            bool match = false;
            for(type::size i = offset;i<__size;i++)
            {
                match = false;
                for(type::size j = 0;!match && j<buf.size();j++)
                {
                    match = (__bytes[i]==buf[j]);
                }
                if(!match) { return i; }
            }
        }
    }
    else
    {
        if(match==entire)
        {
            if(buf.size()<=__size && buf.size()>0)
            {
                /** adjust offset */
                offset = __size - buf.size() < offset ? __size - buf.size() : offset;
                for(type::size i = offset;i+1>0;i--)
                {
                    if(buf.compare(&__bytes[offset],i,buf.size())==0) { return i; }
                }
            }
        }
        else if(match==partial)
        {
            /** adjust offset */
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;i--)
            {
                for(type::size j = 0;j<buf.size();j++)
                {
                    if(__bytes[i]==buf[j]) { return i; }
                }
            }
        }
        else
        {
            /** adjust offset */
            bool match = false;
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;i--)
            {
                match = false;
                for(type::size j = 0;!match && j<buf.size();j++)
                {
                    match = (__bytes[i]==buf[j]);
                }
                if(!match) { return i; }
            }
        }
    }
    return eop;
}

/**
 * @fn              inline int continuous::compare(type::size offset,type::size n,const type::character * str,type::size position,type::size length)  const
 * @brief           compare
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int Continuous::compare(type::size offset,type::size n,const char* str,type::size position,type::size length)  const
{
    if(str!=nullptr)
    {
        if(length==eop)
        {
            length = ::strlen(str);
            position = position < length ? position : length;
            length = length - position;
        }
    }
    else
    {
        position = 0;
        length = 0;
    }
    /** adjust offset */
    if(__size < offset){ offset = __size; }
    /** ajdust n */
    n = __size - offset < n ? __size - offset : n;
    return n==length ? (n!=0 ? ::strncmp((char *) &__bytes[offset],&str[position],n) : 0) : (n>length ? 1 : -1);
}

/**
 * @fn              inline int continuous::compare(type::size offset,type::size n,const type::character * str,type::size position,type::size length)  const
 * @brief           compare
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int Continuous::compare(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length) const
{
    return compare(offset,n,(char *) bytes,position,length);
}

/**
 * @fn              inline int continuous::compare(const type::byte * bytes,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int Continuous::compare(const type::byte * bytes,type::size position,type::size length) const
{
    return compare(0,__size,bytes,position,length);
}

/**
 * @fn              inline int continuous::compare(const type::byte * bytes,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | bytes | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 */
inline int Continuous::compare(const char * bytes,type::size position,type::size length) const
{
        return compare(0,__size,bytes,position,length);
}

/**
 * @fn              inline int continuous::compare(type::size offset,type::size n,const ds::buffer & buf,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ...|
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int Continuous::compare(type::size offset,type::size n,const Buffer & buf,type::size position,type::size length) const
{
    /** adjust offset */
    if(__size < offset){ offset = __size; }
    /** ajdust n */
    n = __size - offset < n ? __size - offset : n;
    return buf.compare(position,length,__bytes,offset,n);
}

/**
 * @fn              inline int continuous::compare(const ds::buffer & buf,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int Continuous::compare(const Buffer & buf,type::size position,type::size length) const
{
    return buf.compare(position,length,__bytes,0,__size);
}
/**
 * @fn              inline ds::buffer * continuous::duplicate(void)
 * @brief           duplicate
 * @details
 * @return          | ds::buffer * | ... |
 */
inline Buffer * Continuous::duplicate(void)
{
    return new Continuous(*this);
}

inline void Continuous::position(type::size position)
{
    if(position < __size)
    {
        erase(position + 1);
    }
    else if(position > __size && position <= __capacity)
    {
        __size = position;
    }
}

} } }

#endif // __NOVEMBERIZING_IO_BUFFERS__CONTINUOUS__INLINE__HH__
