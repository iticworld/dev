#ifndef   __NOVEMBERIZING_IO_BUFFERS__CONTINUOUS__HH__
#define   __NOVEMBERIZING_IO_BUFFERS__CONTINUOUS__HH__

#include <novemberizing/io/buffer.hh>
#include <novemberizing/ds/throwable.hh>

#include <stdio.h>

namespace novemberizing { namespace io { namespace buffers {

class Continuous : public Buffer
{
protected:  type::byte * __bytes;
protected:  type::size __size;
protected:  type::size __capacity;
public:     inline virtual void position(type::size position);
public:     inline virtual type::size capacity(void) const;
public:     inline virtual type::size size(void) const;
public:     inline virtual void capacity(type::size value);
public:     inline virtual void resize(type::size value,int c = 0);
public:     inline virtual int erase(type::size offset = 0,type::size n = eop);
public:     inline virtual void clear(void);
public:     inline virtual type::byte & at(type::size index);
public:     inline virtual const type::byte & at(type::size index) const;
public:     inline virtual type::byte & operator[](type::size index);
public:     inline virtual const type::byte & operator[](type::size index) const;
public:     inline virtual type::size copy(type::byte * out,type::size offset = 0,type::size n = eop) const;
public:     inline virtual type::size copy(char * out,type::size offset = 0,type::size n = eop) const;
public:     inline virtual type::byte * back(void);
public:     inline virtual const type::byte * back(void) const;
public:     inline virtual type::byte * front(void);
public:     inline virtual const type::byte * front(void) const;
public:     inline virtual const type::byte * front(type::size & len) const;
public:     inline virtual type::byte * front(type::size & len);
public:     inline virtual const type::byte * back(type::size & len) const;
public:     inline virtual type::byte * back(type::size & len);
public:     inline virtual type::size remain(void) const;
public:     inline virtual int assign(const type::byte * bytes,type::size position = 0,type::size length = eop);
public:     inline virtual int assign(const char * str,type::size position = 0,type::size length = eop);
public:     inline virtual int assign(const Buffer & buf,type::size position = 0,type::size length = eop);
public:     inline virtual int assign(type::byte byte,type::size length = 1);
public:     inline virtual int assign(char character,type::size length = 1);
public:     inline virtual int append(const type::byte * bytes,type::size position = 0,type::size length = eop);
public:     inline virtual int append(const char * str,type::size position = 0,type::size length = eop);
public:     inline virtual int append(const Buffer & buf,type::size position = 0,type::size length = eop);
public:     inline virtual int append(type::byte byte,type::size length = 1);
public:     inline virtual int append(char character,type::size length = 1);
public:     inline virtual int insert(type::size offset,const type::byte * bytes,type::size position = 0,type::size length = eop);
public:     inline virtual int insert(type::size offset,const char * str,type::size position = 0,type::size length = eop);
public:     inline virtual int insert(type::size offset,const Buffer & buf,type::size position = 0,type::size length = eop);
public:     inline virtual int insert(type::size offset,type::byte byte,type::size length = 1);
public:     inline virtual int insert(type::size offset,char character,type::size length = 1);
public:     inline virtual int replace(type::size offset,type::size n,const type::byte * bytes,type::size position = 0,type::size length = eop);
public:     inline virtual int replace(type::size offset,type::size n,const char * str,type::size position = 0,type::size length = eop);
public:     inline virtual int replace(type::size offset,type::size n,const Buffer & buf,type::size position = 0,type::size length = eop);
public:     inline virtual int replace(type::size offset,type::size n,type::byte byte,type::size length = 1);
public:     inline virtual int replace(type::size offset,type::size n,char character,type::size length = 1);
public:     inline virtual type::size find(type::size offset,const type::byte * bytes,Direction direction = forward,Match match = entire);
public:     inline virtual type::size find(type::size offset,const type::byte * bytes,type::size position,type::size length,Direction direction = forward,Match match = entire);
public:     inline virtual type::size find(type::size offset,const char * str,Direction direction = forward,Match match = entire);
public:     inline virtual type::size find(type::size offset,const char * str,type::size position,type::size length,Direction direction = forward,Match match = entire);
public:     inline virtual type::size find(type::size offset,const Buffer & buf,Direction direction = forward,Match match = entire);
public:     inline virtual type::size find(type::size offset,char character,Direction direction = forward,Match match = entire);
public:     inline virtual type::size find(type::size offset,type::byte byte,Direction direction = forward,Match match = entire);
public:     inline virtual int compare(const type::byte * bytes,type::size position = 0,type::size length = eop) const;
public:     inline virtual int compare(const char * str,type::size position = 0,type::size length = eop) const;
public:     inline virtual int compare(const Buffer & buf,type::size position = 0,type::size length = eop) const;
public:     inline virtual int compare(type::size offset,type::size n,const type::byte * bytes,type::size position = 0,type::size length = eop) const;
public:     inline virtual int compare(type::size offset,type::size n,const char * str,type::size position = 0,type::size length = eop) const;
public:     inline virtual int compare(type::size offset,type::size n,const Buffer & buf,type::size position = 0,type::size length = eop) const;
public:     inline virtual Buffer * duplicate(void);
public:     inline Continuous(void);
public:     inline Continuous(type::size page);
public:     inline Continuous(const Continuous & x);
public:     inline Continuous(const char * str,type::size position = 0,type::size length = eop,type::size page = 0);
public:     inline Continuous(const type::byte * bytes,type::size position = 0,type::size length = eop,type::size page = 0);
public:     inline Continuous(const Buffer & buf,type::size position = 0,type::size length = eop,type::size page = 0);
public:     inline Continuous(type::byte byte,type::size length,type::size page = 0);
public:     inline Continuous(char character,type::size length,type::size page = 0);
public:     inline virtual ~Continuous(void);
};

} } }

#include <novemberizing/io/buffers/continuous.inline.hh>

#endif // __NOVEMBERIZING_IO_BUFFERS__CONTINUOUS__HH__
