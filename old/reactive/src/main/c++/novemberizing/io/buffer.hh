#ifndef   __NOVEMBERIZING_IO__BUFFER__HH__
#define   __NOVEMBERIZING_IO__BUFFER__HH__

#include <novemberizing/concurrency/sync.hh>

namespace novemberizing { namespace io {

/**
 * @class       Buffer
 * @brief
 * @details
 */
class Buffer : public concurrency::Sync
{
protected:  type::size __page;
public:     typedef enum __match {
                entire = 0,
                partial,
                without,
            } Match;
public:     typedef enum __direction {
                forward = 0,
                backward = 1,
            } Direction;
public:     static const type::size eop = -1L;
public:     virtual void position(type::size position) = 0;
public:     inline virtual type::size page(void) const;
public:     virtual type::size capacity(void) const = 0;
public:     virtual type::size size(void) const = 0;
public:     inline virtual void page(type::size value);
public:     virtual void capacity(type::size value) = 0;
public:     virtual void resize(type::size value,int c = 0) = 0;
public:     virtual int erase(type::size offset = 0,type::size n = eop) = 0;
public:     virtual void clear(void) = 0;
public:     virtual type::byte & at(type::size index) = 0;
public:     virtual const type::byte & at(type::size index) const = 0;
public:     virtual type::byte & operator[](type::size index) = 0;
public:     virtual const type::byte & operator[](type::size index) const = 0;
public:     virtual type::size copy(type::byte * out,type::size offset = 0,type::size n = eop) const = 0;
public:     virtual type::size copy(char * out,type::size offset = 0,type::size n = eop) const = 0;
public:     virtual type::byte * front(void) = 0;
public:     virtual const type::byte * front(void) const = 0;
public:     virtual type::byte * back(void) = 0;
public:     virtual const type::byte * back(void) const = 0;
public:     virtual const type::byte * front(type::size & len) const = 0;
public:     virtual type::byte * front(type::size & len) = 0;
public:     virtual const type::byte * back(type::size & len) const = 0;
public:     virtual type::byte * back(type::size & len) = 0;
public:     virtual type::size remain(void) const = 0;
public:     virtual int assign(const type::byte * bytes,type::size position = 0,type::size length = eop) = 0;
public:     virtual int assign(const char * str,type::size position = 0,type::size length = eop) = 0;
public:     virtual int assign(const Buffer & buf,type::size position = 0,type::size length = eop) = 0;
public:     virtual int assign(type::byte byte,type::size length = 1) = 0;
public:     virtual int assign(char character,type::size length = 1) = 0;
public:     virtual int append(const type::byte * bytes,type::size position = 0,type::size length = eop) = 0;
public:     virtual int append(const char * str,type::size position = 0,type::size length = eop) = 0;
public:     virtual int append(const Buffer & buf,type::size position = 0,type::size length = eop) = 0;
public:     virtual int append(type::byte byte,type::size length = 1) = 0;
public:     virtual int append(char character,type::size length = 1) = 0;
public:     virtual int insert(type::size offset,const type::byte * bytes,type::size position = 0,type::size length = eop) = 0;
public:     virtual int insert(type::size offset,const char * str,type::size position = 0,type::size length = eop) = 0;
public:     virtual int insert(type::size offset,const Buffer & buf,type::size position = 0,type::size length = eop) = 0;
public:     virtual int insert(type::size offset,type::byte byte,type::size length = 1) = 0;
public:     virtual int insert(type::size offset,char character,type::size length = 1) = 0;
public:     virtual int replace(type::size offset,type::size n,const type::byte * bytes,type::size position = 0,type::size length = eop) = 0;
public:     virtual int replace(type::size offset,type::size n,const char * str,type::size position = 0,type::size length = eop) = 0;
public:     virtual int replace(type::size offset,type::size n,const Buffer & buf,type::size position = 0,type::size length = eop) = 0;
public:     virtual int replace(type::size offset,type::size n,type::byte byte,type::size length = 1) = 0;
public:     virtual int replace(type::size offset,type::size n,char character,type::size length = 1) = 0;
public:     virtual type::size find(type::size offset,const char * str,Direction direction = forward,Match match = entire) = 0;
public:     virtual type::size find(type::size offset,const char * str,type::size position,type::size length,Direction direction = forward,Match match = entire) = 0;
public:     virtual type::size find(type::size offset,const type::byte * bytes,Direction direction = forward,Match match = entire) = 0;
public:     virtual type::size find(type::size offset,const type::byte * bytes,type::size position,type::size length,Direction direction = forward,Match match = entire) = 0;
public:     virtual type::size find(type::size offset,const Buffer & buf,Direction direction = forward,Match match = entire) = 0;
public:     virtual type::size find(type::size offset,char character,Direction direction = forward,Match match = entire) = 0;
public:     virtual type::size find(type::size offset,type::byte byte,Direction direction = forward,Match match = entire) = 0;
public:     virtual int compare(const type::byte * bytes,type::size position = 0,type::size length = eop) const = 0;
public:     virtual int compare(const char * str,type::size position = 0,type::size length = eop) const = 0;
public:     virtual int compare(const Buffer & buf,type::size position = 0,type::size length = eop) const = 0;
public:     virtual int compare(type::size offset,type::size n,const type::byte * bytes,type::size position = 0,type::size length = eop) const = 0;
public:     virtual int compare(type::size offset,type::size n,const Buffer & buf,type::size position = 0,type::size length = eop) const = 0;
public:     virtual int compare(type::size offset,type::size n,const char * str,type::size position = 0,type::size length = eop) const = 0;
public:     virtual Buffer * duplicate(void) = 0;
public:     inline Buffer(void);
public:     inline virtual ~Buffer(void);
};

} }

#include <novemberizing/io/buffer.inline.hh>

#endif // __NOVEMBERIZING_IO__BUFFER__HH__
