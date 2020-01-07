#ifndef   __NOVEMBERIZING_IO_BUFFERS__LIST__INLINE__HH__
#define   __NOVEMBERIZING_IO_BUFFERS__LIST__INLINE__HH__

namespace novemberizing { namespace io { namespace buffers {

inline List::List(void)
{
    __size = 0;
    __capacity = 0;
    __page = 0;
}

inline List::List(type::size page)
{
    __size = 0;
    __capacity = 0;
    __page = page;

    capacity(__page);
}

inline List::List(const List & x)
{
    __size = x.__size;
    __capacity = x.__capacity;
    __page = x.__page;

    for(std::list<Buffer *>::const_iterator it = x.__list.cbegin();it!=x.__list.cend();++it)
    {
        Buffer * b = *it;
        if(b!=nullptr)
        {
            /** implement duplicate */
            __list.push_back(b->duplicate());
        }
    }
}

/**
 * @fn              inline list::list(const type::character * str,type::size position,type::size length,type::size page)
 * @brief           constructor of ds::buffers::list
 * @details
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @param [in]      | page | type::size | 0 | ... |
 */
inline List::List(const char * str,type::size position,type::size length,type::size page)
{
    __page = page;
    __capacity = 0;
    __size = 0;

    assign(str,position,length);
}

/**
 * @fn              inline list::list(const type::byte * bytes,type::size position,type::size length,type::size page)
 * @brief           constructor of ds::buffers::list
 * @details
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @param [in]      | page | type::size | 0 | ... |
 */
inline List::List(const type::byte * bytes,type::size position,type::size length,type::size page)
{
    __page = page;
    __capacity = 0;
    __size = 0;

    assign(bytes,position,length);
}

/**
 * @fn              inline list::list(const ds::buffer & buf,type::size position,type::size length,type::size page)
 * @brief           constructor of ds::buffers::list
 * @details
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @param [in]      | page | type::size | 0 | ... |
 */
inline List::List(const Buffer & buf,type::size position,type::size length,type::size page)
{
    __page = page;
    __capacity = 0;
    __size = 0;

    assign(buf,position,length);
}

/**
 * @fn              inline list::list(type::byte byte,type::size length,type::size page)
 * @brief           constructor of ds::buffers::list
 * @details
 * @param [in]      | byte | type::byte | - | ... |
 * @param [in]      | length | type::size | - | ... |
 * @param [in]      | page | type::size | 0 | ... |
 */
inline List::List(type::byte byte,type::size length,type::size page)
{
    __page = page;
    __capacity = 0;
    __size = 0;

    assign(byte,length);
}

/**
 * @fn              inline list::list(type::character character,type::size length,type::size page)
 * @brief           constructor of ds::buffers::list
 * @details
 * @param [in]      | character | type::character | - | ... |
 * @param [in]      | length | type::size | - | ... |
 * @param [in]      | page | type::size | 0 | ... |
 */
inline List::List(char character,type::size length,type::size page)
{
    __page = page;
    __capacity = 0;
    __size = 0;

    assign(character,length);
}

inline List::~List(void)
{
    __page = 0;
    __capacity = 0;
    __size = 0;

    for(std::list<Buffer *>::iterator it = __list.begin();it!=__list.end();it = __list.erase(it))
    {
        Buffer * b = *it;
        if(b!=nullptr)
        {
            delete b;
        }
    }
}

/**
 * @fn              inline type::size list::capacity(void) const
 * @brief           capacity
 * @details
 * @return          | type::size | ... |
 */
inline type::size List::capacity(void) const { return __capacity; }

/**
 * @fn              inline type::size list::size(void) const
 * @brief           size
 * @details
 * @return          | type::size | ... |
 */
inline type::size List::size(void) const { return __size; }

/**
 * @fn              inline void list::___append(type::size n)
 * @brief           append n'th empty space
 * @details
 * @param [in]      | n | type::size | - | ... |
 */
inline Buffer * List::___append(type::size n)
{
    Buffer * ret = nullptr;
    if(n>0)
    {
        if(__list.size()==0)
        {
            Continuous * b = new Continuous();
            b->capacity(n);
            __list.push_back(b);
            ret = b;
        }
        else
        {
            if(__list.back()->remain()>0 || __list.back()->capacity()<__page)
            {
                __list.back()->capacity(__list.back()->capacity() + n);
                ret = __list.back();
            }
            else
            {
                Continuous * b = new Continuous();
                b->capacity(n);
                __list.push_back(b);
                ret = b;
            }
        }
        __capacity += n;
    }
    return ret;
}

/**
 * @fn              inline std::list<ds::buffer *>::iterator list::___find(std::list<ds::buffer *>::iterator it,type::size until,type::size & idx) const
 * @brief           find
 * @details
 * @param [in]      | it | std::list<ds::buffer *>::iterator | - | ... |
 * @param [in]      | until | type::size | - | ... |
 * @param [in,out]  | idx | type::size & | - | ... |
 * @return          | std::list<ds::buffer *>::iterator | ... |
 */
inline std::list<Buffer *>::const_iterator List::___find(std::list<Buffer *>::const_iterator it,type::size until,type::size & idx) const
{
    for(;it!=__list.end();++it)
    {
        Buffer * b = *it;
        if(idx + b->size()<=until)
        {
            return it;
        }
        else
        {
            idx += b->size();
        }
    }
    return __list.end();
}

inline std::list<Buffer *>::const_reverse_iterator List::___rfind(std::list<Buffer *>::const_reverse_iterator rit,type::size until,type::size & idx) const
{
    for(;rit!=__list.rend();++rit)
    {
        Buffer * b = *rit;
        if(idx - b->size()<=until)
        {
            return rit;
        }
        else
        {
            idx -= b->size();
        }
    }
    return __list.rend();
}

/**
 * @fn              inline int list::___compare(std::list<ds::buffer *>::const_iterator it,type::size local,const type::character * str,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | it | std::list<ds::buffer * >::iterator | - | ... |
 * @param [in]      | local | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | - | ... |
 * @param [in]      | length | type::size | - | ... |
 * @return          | int | ... |
 */
inline int List::___compare(std::list<Buffer *>::const_iterator it,type::size local,const char * str,type::size position,type::size length) const
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
    for(;length!=0 && it!=__list.end();++it)
    {
        Buffer * b = *it;
        for(type::size i=local;i<b->size() && length!=0;i++)
        {
            if(str[position]!=b->at(i))
            {
                return 1;
            }
            position++;
            length--;
        }
        if(length==0){ return 0; }
        local = 0;
    }
    return -1;
}

/**
 * @fn              inline std::list<ds::buffer *>::iterator list::___find(type::size until,type::size & idx)
 * @brief           find iterator util position
 * @details
 * @param [in]      | until | type::size | - | ... |
 * @param [in,out]  | idx | type::size & | - | ... |
 * @return          | std::list<ds::buffer *>::iterator | ... |
 */
inline std::list<Buffer *>::const_iterator List::___find(type::size until,type::size & idx) const
{
    for(std::list<Buffer *>::const_iterator it = __list.begin();it!=__list.end();)
    {
        Buffer * b = *it;
        if(b!=nullptr)
        {
            if(idx+b->size()<=until)
            {
                idx += b->size();
                ++it;
            }
            else
            {
                return it;
            }
        }
        else
        {
            /** never executed this code. */
            ++it;
        }
    }
    return __list.end();
}

/**
 * @fn              inline std::list<ds::buffer *>::iterator list::___find(type::size until,type::size & idx)
 * @brief           find iterator util position
 * @details
 * @param [in]      | until | type::size | - | ... |
 * @param [in,out]  | idx | type::size & | - | ... |
 * @return          | std::list<ds::buffer *>::iterator | ... |
 */
inline std::list<Buffer *>::iterator List::___find(type::size until,type::size & idx)
{
    for(std::list<Buffer *>::iterator it = __list.begin();it!=__list.end();)
    {
        Buffer * b = *it;
        if(b!=nullptr)
        {
            if(idx+b->size()<=until)
            {
                idx += b->size();
                ++it;
            }
            else
            {
                return it;
            }
        }
        else
        {
            /** never executed this code. */
            it = __list.erase(it);
        }
    }
    return __list.end();
}

inline void List::___erase(std::list<Buffer *>::iterator it)
{
    for(;it!=__list.end();it = __list.erase(it))
    {
        Buffer * b = *it;
        if(b!=nullptr)
        {
            __capacity -= b->capacity();
            __size -= b->size();
            delete b;
        }
    }
}

/**
 * @fn              inline void list::capacity(type::size value)
 * @brief           set capacity
 * @details
 * @param [in]      | value | type::size | - | ... |
 */
inline void List::capacity(type::size value)
{
    if(__capacity!=value)
    {
        if(__capacity<value)
        {
            ___append(value - __capacity);
            __capacity = value;
        }
        else
        {
            /** value < __capacity */
            if(__size <= value)
            {
                if(__list.size()>0)
                {
                    if(__list.back()->remain()>0)
                    {
                        __list.back()->capacity(__capacity-value);
                        if(__list.back()->size()==0)
                        {
                            delete __list.back();
                            __list.pop_back();
                        }
                    }
                    else
                    {
                        /** never execute this code .. */
                    }
                }
                else
                {
                    /** never execute this code .. */
                }
                __capacity = value;
            }
            else
            {
                type::size idx = 0;
                std::list<Buffer *>::iterator it = ___find(value,idx);
                if(it!=__list.end())
                {
                    /** value < __size */
                    Buffer * b = *it;
                    b->resize(value - idx);
                    if(b->capacity()==0)
                    {
                        ___erase(it=__list.erase(it));
                    }
                    else
                    {
                        ___erase(++it);
                    }
                    __size = value;
                    __capacity = value;
                }
                else
                {
                    /**  not exist removable item */
                }
            }
        }
    }
}

/**
 * @fn              inline void list::resize(type::size value,int c)
 * @brief           resize
 * @details
 * @param [in]      | value | type::size | - | ... |
 * @param [in]      | c | int | 0 | ... |
 */
inline void List::resize(type::size value,int c)
{
    if(__size!=value)
    {
        if(__size < value)
        {
            if(__capacity<value)
            {
                capacity(value);
            }
            Buffer * b = __list.back();
            // if(b==nullptr){ EXCEPTION("exception."); }
            b->append((type::byte) c,value-__size);
            __size = value;
        }
        else
        {
            /** value < __size */
            type::size idx = 0;
            std::list<Buffer *>::iterator it = ___find(value,idx);
            if(it!=__list.end())
            {
                Buffer * b = *it;
                b->resize(value - idx);
                if(b->capacity()==0)
                {
                    ___erase(it=__list.erase(it));
                }
                else
                {
                    ___erase(++it);
                }
                __size = value;
                __capacity = value;
            }
            else
            {
                /**  not exist removable item */
            }
        }
    }
}

/**
 * @fn              int list::erase(type::size offset,type::size n)
 * @brief           erase
 * @details
 * @param [in]      | offset | type::size | 0 | ... |
 * @param [in]      | n | type::size | constant::eop | ... |
 */
int List::erase(type::size offset,type::size n)
{
    if(offset<__size)
    {
        /** adjust */
        n = __size - offset < n ? __size - offset : n;
        if(n>0)
        {
            type::size idx = 0;
            std::list<Buffer *>::iterator it = ___find(offset,idx);
            /** remove */
            type::size removed = n;
            for(;removed!=0 && it!=__list.end();it=__list.erase(it))
            {
                Buffer * b = *it;
                if(b!=nullptr)
                {
                    type::size local = offset - idx;
                    type::size length = b->size() - local < removed ? b->size() - local : removed;
                    /** prepare next */
                    idx += b->size();
                    offset = idx;
                    b->erase(local,length);
                    removed -= length;
                }
            }
            // __capacity -= n;
            __size -= n;
            __capacity = __size + (__list.size()==0 ? 0 : __list.back()->remain());
        }
    }
    return Success;
}

/**
 * @fn              inline void list::clear(void)
 * @brief           clear
 * @details
 */
inline void List::clear(void)
{
    for(std::list<Buffer *>::iterator it = __list.begin();it!=__list.end();it=__list.erase(it))
    {
        Buffer * b = *it;
        if(b!=nullptr)
        {
            delete b;
        }
    }
    __capacity = 0;
    __size = 0;
    if(__page>0){ ___append(__page); }
}

/**
 * @fn              inline type::byte & list::at(type::size index)
 * @brief           type::byte at the position
 * @details
 * @param [in]      | index | type::size | - | ... |
 * @return          | type::byte & | ... |
 */
inline type::byte & List::at(type::size index)
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    type::size offset = 0;
    std::list<Buffer *>::const_iterator it = ___find(index,offset);
    /** if(it!=__list.end()) throw execption */
    return (*it)->at(index-offset);
}

/**
 * @fn              const type::byte & list::at(type::size index) const
 * @brief           type::byte at the position
 * @details
 * @param [in]      | index | type::size | - | ... |
 * @return          | const type::byte & | ... |
 */
const type::byte & List::at(type::size index) const
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    type::size offset = 0;
    std::list<Buffer *>::const_iterator it = ___find(index,offset);
    /** if(it!=__list.end()) throw execption */
    return (*it)->at(index-offset);
}

/**
 * @fn              type::byte & list::operator[](type::size index)
 * @brief           byte at the position
 * @details
 * @param [in]      | index | type::size | - | ... |
 * @return          | type::byte & | ... |
 */
type::byte & List::operator[](type::size index)
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    type::size offset = 0;
    std::list<Buffer *>::const_iterator it = ___find(index,offset);
    /** if(it!=__list.end()) throw execption */
    return (*it)->at(index-offset);
}

/**
 * @fn              const type::byte & list::operator[](type::size index) const
 * @brief           byte at the index
 * @details
 * @param [in]      | index | type::size | - | ... |
 * @return          | const type::byte & | ... |
 */
const type::byte & List::operator[](type::size index) const
{
    // if(__size<=index){ EXCEPTION("__size<=index"); }
    type::size offset = 0;
    std::list<Buffer *>::const_iterator it = ___find(index,offset);
    /** if(it!=__list.end()) throw execption */
    return (*it)->at(index-offset);
}

/**
 * @fn              type::size list::copy(type::byte * out,type::size offset,type::size n) const
 * @brief           copy
 * @details
 * @param [in]      | out | type::byte * | - | ... |
 * @param [in]      | offset | type::size | 0 | ... |
 * @param [in]      | n | type::size | constant::eop | ... |
 * @return          | type::size | ... |
 */
inline type::size List::copy(type::byte * out,type::size offset,type::size n) const
{
    /** validate */
    if(offset<__size)
    {
        /** adjust */
        n = __size - offset < n ? __size - offset : n;
        type::size idx = 0;
        std::list<Buffer *>::const_iterator it = ___find(offset,idx);
        /** must be found */
        type::size removed = n;
        for(;removed!=0 && it!=__list.end();++it)
        {
            Buffer * b = *it;
            if(b!=nullptr)
            {
                type::size local = offset - idx;
                type::size length = b->size() - local < removed ? b->size() - local : removed;
                idx += b->size();
                offset = idx;
                b->copy(&out[n - removed],offset - idx,length);
                removed -= length;
            }
            else
            {
                /** critical */
            }
        }
        return n;
    }
    return 0;
}

/**
 * @fn              inline type::size list::copy(type::character * out,type::size offset,type::size n) const
 * @brief           copy
 * @details
 * @param [in]      | out | type::character * | - | ... |
 * @param [in]      | offset | type::size | 0 | ... |
 * @param [in]      | n | type::size | constant::eop | ... |
 * @return          | type::size | ... |
 */
inline type::size List::copy(char * out,type::size offset,type::size n) const
{
    return copy((type::byte *) out,offset,n);
}

inline type::byte * List::front(void)
{
    return __list.size()>0 ? __list.front()->front() : nullptr;
}

inline const type::byte * List::front(void) const
{
    return __list.size()>0 ? __list.front()->front() : nullptr;
}

inline type::byte * List::back(void)
{
    return __list.size()>0 ? __list.back()->back() : nullptr;
}

inline const type::byte * List::back(void) const
{
    return __list.size()>0 ? __list.back()->back() : nullptr;
}

/**
 * @fn              const type::byte * list::front(type::size & len) const
 * @brief           front of ds::buffers::list
 * @details         it is not different to ds::buffers::continuous,
 *                  it do not contain full contents, only contain list's front.
 * @param [in]      | len | type::size & | - | ... |
 * @return          | const type::byte * | ... |
 */
inline const type::byte * List::front(type::size & len) const
{
    return __list.size()>0 ? __list.front()->front(len) : nullptr;
}

/**
 * @fn              inline type::byte * front(type::size & len)
 * @brief           front of ds::buffers::list
 * @details         it is not different to ds::buffers::continuous,
 *                  it do not contain full contents, only contain list's front.
 * @param [in]      | len | type::size & | - | ... |
 * @return          | type::byte * | ... |
 */
inline type::byte * List::front(type::size & len)
{
    return __list.size()>0 ? __list.front()->front(len) : nullptr;
}

/**
 * @fn              const type::byte * list::back(type::size & len) const
 * @brief           back of ds::buffers::list
 * @details
 * @param [in]      | len | type::size & | - | ... |
 * @return          | const type::byte * | ... |
 */
inline const type::byte * List::back(type::size & len) const
{
    return __list.size()>0 ? (__list.back()->remain()>0 ? __list.back()->back(len) : nullptr) : nullptr;
}

/**
 * @fn              type::byte * list::back(type::size & len)
 * @brief           back of ds::buffers::list
 * @details
 * @param [in]      | len | type::size & | - | ... |
 * @return          | type::byte * | ... |
 */
inline type::byte * List::back(type::size & len)
{
    return __list.size()>0 ? (__list.back()->remain()>0 ? __list.back()->back(len) : nullptr) : nullptr;
}

/**
 * @fn              inline type::size list::remain(void) const
 * @brief           remain
 * @details
 * @return          | type::size | ... |
 */
inline type::size List::remain(void) const
{
    return __capacity - __size;
}

/**
 * @fn              int list::assign(const type::byte * bytes,type::size position,type::size length)
 * @brief           assign
 * @details
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::assign(const type::byte * bytes,type::size position,type::size length)
{
    return assign((char *) bytes,position,length);
}

/**
 * @fn              int list::assign(const type::character * str,type::size position,type::size length)
 * @brief           assign
 * @details
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::assign(const char * str,type::size position,type::size length)
{
    clear();
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
    if(length>0)
    {
        if(remain()==0)
        {
            ___append(length);
        }
        __list.back()->assign(str,position,length);
        __size = length;
        __capacity = (__size + __list.back()->remain());
    }
    return Success;

}

/**
 * @fn              int list::assign(const ds::buffer & buf,type::size position,type::size length)
 * @brief           assign
 * @details
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::assign(const Buffer & buf,type::size position,type::size length)
{
    clear();
    /** adjust */
    if(position < buf.size())
    {
        length = buf.size() - position < length ? buf.size() - position : length;
        if(length>0)
        {
            if(remain()<length)
            {
                ___append(length - remain());
            }
            type::size remain = 0;
            buf.copy(back(remain),position,length);
            __list.back()->position(length);
            /**  */
            /** increase size */
            __size = length;
            __capacity = (__size + __list.back()->remain());
        }
    }
    return Success;
}

/**
 * @fn              int list::assign(type::byte byte,type::size length)
 * @brief           assign
 * @details
 * @param [in]      | byte | type::byte | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::assign(type::byte byte,type::size length)
{
    clear();
    if(length>0)
    {
        if(remain()==0)
        {
            ___append(length);
        }
        __list.back()->assign(byte,length);
        __size = length;
        __capacity = (__size + __list.back()->remain());
    }
    return Success;
}

/**
 * @fn              int list::assign(type::character character,type::size length)
 * @brief           assign
 * @details
 * @param [in]      | character | type::character | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::assign(char character,type::size length)
{
    return assign((type::byte) character,length);
}

/**
 * @fn              inline int list::append(const type::character * str,type::size position,type::size length)
 * @brief           append
 * @details
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::append(const char * str,type::size position,type::size length)
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
    if(length>0)
    {
        if(remain()==0)
        {
            ___append(length);
        }
        /** remain is exist */
        __list.back()->append(str,position,length);
        __size += length;
        __capacity = (__size + __list.back()->remain());
    }
    return Success;
}

/**
 * @fn              inline int list::append(const type::byte * bytes,type::size position,type::size length)
 * @brief           append
 * @details
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::append(const type::byte * bytes,type::size position,type::size length)
{
    return append((char *) bytes,position,length);
}

/**
 * @fn              inline int list::append(const ds::buffer & buf,type::size position,type::size length)
 * @brief           append
 * @details
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::append(const Buffer & buf,type::size position,type::size length)
{
    if(position < buf.size())
    {
        length = buf.size() - position < length ? buf.size() - position : length;
        if(length>0)
        {
            if(remain()<length)
            {
                ___append(length - remain());
            }
            type::size remain = 0;
            buf.copy(back(remain),position,length);
            __list.back()->position(__list.back()->size() + length);
            __size += length;
            __capacity = (__size + __list.back()->remain());
        }
    }
    return Success;
}

/**
 * @fn              inline int list::append(type::byte byte,type::size length)
 * @brief           append
 * @details
 * @param [in]      | byte | type::byte | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::append(type::byte byte,type::size length)
{
    if(length>0)
    {
        if(remain()==0)
        {
            ___append(length);
        }
        __list.back()->append(byte,length);
        __size += length;
        __capacity = (__size + __list.back()->remain());
    }
    return Success;
}

/**
 * @fn              inline int list::append(type::character character,type::size length)
 * @brief           append
 * @details
 * @param [in]      | character | type::character | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::append(char character,type::size length)
{
    return append((type::byte) character,length);
}

/**
 * @fn              inline int list::insert(type::size offset,const type::character * str,type::size position,type::size length)
 * @brief           insert
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::insert(type::size offset,const char * str,type::size position,type::size length)
{
    int ret = Fail;
    if(offset<__size)
    {
        type::size idx = 0;
        std::list<Buffer *>::const_iterator it = ___find(offset,idx);
        Buffer * b = *it;
        type::size old = b->size();
        ret = b->insert(offset-idx,str,position,length);
        __size += (b->size() - old);
        __capacity = (__size + __list.back()->remain());
    }
    else
    {
        ret = append(str,position,length);
    }
    return ret;
}

/**
 * @fn              int list::insert(type::size offset,const type::byte * bytes,type::size position,type::size length)
 * @brief           insert
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::insert(type::size offset,const type::byte * bytes,type::size position,type::size length)
{
    return insert(offset,(char *) bytes,position,length);
}

/**
 * @fn              inline int list::insert(type::size offset,const ds::buffer & buf,type::size position,type::size length)
 * @brief           insert
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::insert(type::size offset,const Buffer & buf,type::size position,type::size length)
{
    int ret = Fail;
    if(offset < __size)
    {
        if(position < buf.size())
        {
            length = buf.size() - position < length ? buf.size() - position : length;
            if(length>0)
            {
                type::byte * out = (type::byte *) ::malloc(length);
                buf.copy(out,position,length);
                ret = insert(offset,out,0,length);
                ::free(out);
            }
        }
        else
        {
            /** no insert content */
        }
        ret = Success;
    }
    else
    {
        ret = append(buf,position,length);
    }
    return ret;
}

/**
 * @fn              inline int list::insert(type::size offset,type::byte byte,type::size length)
 * @brief           insert
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | byte | type::byte | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::insert(type::size offset,type::byte byte,type::size length)
{
    int ret = Success;
    if(length>0)
    {
        if(offset<__size)
        {
            type::size idx = 0;
            std::list<Buffer *>::const_iterator it = ___find(offset,idx);
            Buffer * b = *it;
            type::size old = b->size();
            b->insert(offset - idx,byte,length);
            __size += (b->size() - old);
            __capacity = (__size + __list.back()->remain());
            ret = Success;
        }
        else
        {
            ret = append(byte,length);
        }
    }
    return ret;
}

/**
 * @fn              int list::insert(type::size offset,type::character character,type::size length)
 * @brief           insert
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | character | type::character | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
int List::insert(type::size offset,char character,type::size length)
{
    return insert(offset,(type::byte) character , length);
}

/**
 * @fn              int list::replace(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length)
 * @brief           replace
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | bytes | const type::bytes * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::replace(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length)
{
    offset = offset < __size ? offset : __size;
    erase(offset,n);
    return insert(offset,bytes,position,length);
}

/**
 * @fn              inline int list::replace(type::size offset,type::size n,const type::character * str,type::size position,type::size length)
 * @brief           replace
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::replace(type::size offset,type::size n,const char * str,type::size position,type::size length)
{
    offset = offset < __size ? offset : __size;
    erase(offset,n);
    return insert(offset,str,position,length);
}

/**
 * @fn              inline int list::replace(type::size offset,type::size n,const ds::buffer & buf,type::size position,type::size length)
 * @brief           replace
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::replace(type::size offset,type::size n,const Buffer & buf,type::size position,type::size length)
{
    offset = offset < __size ? offset : __size;
    erase(offset,n);
    return insert(offset,buf,position,length);
}

/**
 * @fn              inline int list::replace(type::size offset,type::size n,type::byte byte,type::size length)
 * @brief           replace
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | byte | type::byte | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::replace(type::size offset,type::size n,type::byte byte,type::size length)
{
    offset = offset < __size ? offset : __size;
    erase(offset,n);
    return insert(offset,byte,length);
}

/**
 * @fn              inline int list::replace(type::size offset,type::size n,type::character character,type::size length)
 * @brief           replace
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | character | type::character | - | ... |
 * @param [in]      | length | type::size | 1 | ... |
 * @return          | int | ... |
 */
inline int List::replace(type::size offset,type::size n,char character,type::size length)
{
    offset = offset < __size ? offset : __size;
    erase(offset,n);
    return insert(offset,character,length);
}

/**
 * @fn              inline type::size list::find(type::size offset,const type::character * str,type::size position,type::size length,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | - | ... |
 * @param [in]      | length | type::size | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return          | type::size | ... |
 */
inline type::size List::find(type::size offset,const char * str,type::size position,type::size length,Direction direction,Match match)
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
    if(direction==forward)
    {
        if(match==entire)
        {
            if(length<=__size && length>0)
            {
                std::list<Buffer *>::const_iterator current = __list.cbegin();
                type::size idx = 0;
                for(type::size i = offset;i<__size - length + 1;++i)
                {
                    current = ___find(current,i,idx);
                    if(current!=__list.end())
                    {
                        if(___compare(current,i - idx,str,position,length)==0) { return i; }
                    }
                }
            }
        }
        else if(match==partial)
        {
            std::list<Buffer *>::const_iterator current = __list.cbegin();
            type::size idx = 0;
            for(type::size i = offset;i<__size;++i)
            {
                current = ___find(current,i,idx);
                if(current!=__list.end())
                {
                    Buffer * b = *current;
                    type::byte byte = b->at(i - idx);
                    for(type::size j=0;j<length;++j)
                    {
                        if(str[j+position]==byte) { return i; }
                    }
                }
            }
        }
        else
        {
            std::list<Buffer *>::const_iterator current = __list.cbegin();
            type::size idx = 0;
            bool match = false;
            for(type::size i = offset;i<__size;++i)
            {
                current = ___find(current,i,idx);
                if(current!=__list.end())
                {
                    match = false;
                    Buffer * b = *current;
                    type::byte byte = b->at(i - idx);
                    for(type::size j=0;!match && j<length;++j)
                    {
                        match = (str[j+position]==byte);
                    }
                    if(!match) { return i; }
                }
            }
        }
    }
    else
    {
        if(match==entire)
        {
            if(length<=__size && length>0)
            {
                offset = __size - length < offset ? __size - length : offset;
                std::list<Buffer *>::const_reverse_iterator rit = __list.crbegin();
                type::size idx = __size;
                for(type::size i = offset;i+1>0;--i)
                {
                    rit = ___rfind(rit,i,idx);
                    /**
                     * http://www.cplusplus.com/reference/iterator/reverse_iterator/base/
                     *
                     * iterator_byte reverse_iterator::base() const;
                     * return base iterator
                     * returns a copy of the base iterator.
                     * The base iterator is an iterator of the same type as
                     * the one used to construct the reverse_iterator,
                     * but pointing to the element next to the one the
                     * reverse_iterator is currently pointing to (a
                     * reverse_iterator has always an offset of -1 with
                     * respect to tis base iterator).
                     * @return value
                     * a copy of the base iterator, which iterates in the
                     * opposite direction.
                     * Member type iterator_type is the underlying bidirectional
                     * iterator type (the class template paramter: Iterator).
                     */
                    std::list<Buffer *>::const_iterator current = rit.base();
                    Buffer * b = *current;
                    if(___compare(current,i - (idx - b->size()),str,position,length)==0) { return i; }
                }
            }
        }
        else if(match==partial)
        {
            std::list<Buffer *>::const_reverse_iterator rit = __list.crbegin();
            type::size idx = __size;
            /** adjust offset */
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;i--)
            {
                rit = ___rfind(rit,i,idx);
                if(rit!=__list.rend())
                {
                    Buffer * b = *rit;
                    type::byte byte = b->at(i - (idx - b->size()));
                    for(type::size j=0;j<length;++j)
                    {
                        if(str[j+position]==byte) { return i; }
                    }
                }
            }
        }
        else
        {
            std::list<Buffer *>::const_reverse_iterator rit = __list.crbegin();
            type::size idx = __size;
            bool match = false;
            /** adjust offset */
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;i--)
            {
                rit = ___rfind(rit,i,idx);
                if(rit!=__list.rend())
                {
                    Buffer * b = *rit;
                    type::byte byte = b->at(i - (idx - b->size()));
                    match = false;
                    for(type::size j=0;!match && j<length;++j)
                    {
                        match = (str[j+position]==byte);
                    }
                    if(!match) { return i; }
                }
            }
        }
    }
    return eop;
}

/**
 * @fn              inline type::size list::find(type::size offset,const type::character * str,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::match | ... |
 */
inline type::size List::find(type::size offset,const char * str,Direction direction,Match match)
{
    return find(offset,str,0,::strlen(str),direction,match);
}

/**
 * @fn              inline type::size list::find(type::size offset,const type::byte * bytes,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | bytes | const type::bytes *  | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return          | type::size | ... |
 */
inline type::size List::find(type::size offset,const type::byte * bytes,Direction direction,Match match)
{
    return find(offset,(char *) bytes,0,::strlen((char *) bytes),direction,match);
}

/**
 * @fn              inline type::size list::find(type::size offset,const type::byte * bytes,type::size position,type::size length,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | - | ... |
 * @param [in]      | length | type::size | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::entire | ... |
 */
inline type::size List::find(type::size offset,const type::byte * bytes,type::size position,type::size length,Direction direction,Match match)
{
    return find(offset,(char *) bytes,position,length,direction,match);
}

/**
 * @fn              inline type::size list::find(type::size offset,type::byte byte,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | byte | type::byte | - | ... |
 * @param [in]      | direction | type::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | type::buffer::match | ds::buffer::entire | ... |
 * @return          | type::size | ... |
 */
inline type::size List::find(type::size offset,type::byte byte,Direction direction,Match match)
{
    if(direction==forward)
    {
        if(match==without)
        {
            std::list<Buffer *>::const_iterator it = __list.cbegin();
            type::size idx = 0;
            for(type::size i = offset;i<__size;++i)
            {
                it = ___find(it,i,idx);
                if(it!=__list.end())
                {
                    Buffer * b = *it;
                    if(b->at(i - idx)!=byte) { return i; }
                }
            }
        }
        else
        {
            std::list<Buffer *>::const_iterator it = __list.cbegin();
            type::size idx = 0;
            for(type::size i = offset;i<__size;++i)
            {
                it = ___find(it,i,idx);
                if(it!=__list.end())
                {
                    Buffer * b = *it;
                    if(b->at(i - idx)==byte) { return i; }
                }
            }
        }
    }
    else
    {
        if(match==without)
        {
            std::list<Buffer *>::const_reverse_iterator rit = __list.crbegin();
            type::size idx = __size;
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;++i)
            {
                Buffer * b = *rit;
                if(b->at(i - (idx - b->size()))!=byte) { return i; }
            }
        }
        else
        {
            std::list<Buffer *>::const_reverse_iterator rit = __list.crbegin();
            type::size idx = __size;
            offset = offset < __size ? offset : __size - 1;
            for(type::size i = offset;i+1>0;++i)
            {
                Buffer * b = *rit;
                if(b->at(i - (idx - b->size()))==byte) { return i; }
            }
        }
    }
    return eop;
}

/**
 * @fn              inline type::size list::find(type::size offset,type::character character,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | character | type::character | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return          | type::size | ... |
 */
inline type::size List::find(type::size offset,char character,Direction direction,Match match)
{
    return find(offset,(type::byte) character,direction,match);
}

/**
 * @fn              inline type::size list::find(type::size offset,const ds::buffer & buf,ds::buffer::direction direction,ds::buffer::match match)
 * @brief           find
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | direction | ds::buffer::direction | ds::buffer::forward | ... |
 * @param [in]      | match | ds::buffer::match | ds::buffer::entire | ... |
 * @return          | type::size | ... |
 */
inline type::size List::find(type::size offset,const Buffer & buf,Direction direction,Match match)
{
    if(buf.size()>0)
    {
        type::byte * bytes = (type::byte *) ::malloc(buf.size());
        buf.copy(bytes,0,buf.size());
        type::size ret = find(offset,bytes,0,buf.size(),direction,match);
        ::free(bytes);
        return ret;
    }
    return eop;
    // return find(offset,)
}

/**
 * @fn              inline int list::compare(type::size offset,type::size n,const type::character * str,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | - | ... |
 * @param [in]      | length | type::size | - | ... |
 * @return          | int | ... |
 */
inline int List::compare(type::size offset,type::size n,const char * str,type::size position,type::size length) const
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
    if(offset<__size)
    {
        n = __size - offset < n ? __size - offset : n;
        if(n==length)
        {
            type::size idx = 0;
            std::list<Buffer *>::const_iterator it = ___find(offset,idx);
            return ___compare(it,offset - idx,str,position,length);
        }
        else
        {
            return n>length ? 1 : -1;
        }
    }
    return -1;
}

/**
 * @fn              inline int list::compare(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | bytes | const type::byte * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::compare(type::size offset,type::size n,const type::byte * bytes,type::size position,type::size length) const
{
    return compare(offset,n,(char *) bytes,position,length);
}

/**
 * @fn              inline int list::compare(const type::character * str,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | str | const type::character * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::compare(const char * str,type::size position,type::size length) const
{
    return compare(0,length,str,position,length);
}

/**
 * @fn              inline int list::compare(const type::byte * bytes,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | bytes | const type::bytes * | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::compare(const type::byte * bytes,type::size position,type::size length) const
{
    return compare(0,length,(char *) bytes,position,length);
}

/**
 * @fn              inline int compare(type::size offset,type::size n,const ds::buffer & buf,type::size position = 0,type::size length = constant::eop) const
 * @brief           compare
 * @details
 * @param [in]      | offset | type::size | - | ... |
 * @param [in]      | n | type::size | - | ... |
 * @param [in]      | buf | const ds::buffer &  | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::compare(type::size offset,type::size n,const Buffer & buf,type::size position,type::size length) const
{
    if(offset<__size)
    {
        n = __size - offset < n ? __size - offset : n;
        if(position < buf.size())
        {
            length = buf.size() - position < length ? buf.size() - position : length;
            if(n==length)
            {
                type::byte * bytes = (type::byte *) ::malloc(n);
                int ret = compare(offset,n,bytes,0,length);
                ::free(bytes);
                return ret;
            }
            return n>length ? 1 : -1;
        }
        return 1;
    }
    return -1;
}

/**
 * @fn              inline int list::compare(const ds::buffer & buf,type::size position,type::size length) const
 * @brief           compare
 * @details
 * @param [in]      | buf | const ds::buffer & | - | ... |
 * @param [in]      | position | type::size | 0 | ... |
 * @param [in]      | length | type::size | constant::eop | ... |
 * @return          | int | ... |
 */
inline int List::compare(const Buffer & buf,type::size position,type::size length) const
{
    if(__size>0)
    {
        if(position < buf.size())
        {
            length = buf.size() - position < length ? buf.size() - position : length;
            if(length>0)
            {
                return compare(0,length,buf,position,length);
            }
            return 1;
        }
        else
        {
            return 1;
        }
    }
    return -1;
}

/**
 * @fn              inline ds::buffer * list::duplicate(void)
 * @brief           duplicate
 * @details
 * @return          | ds::buffer * | ... |
 */
inline Buffer * List::duplicate(void)
{
    return new List(*this);
}

inline void List::position(type::size position)
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

#endif // __NOVEMBERIZING_IO_BUFFERS__LIST__INLINE__HH__
