#ifndef   __NOVEMBERIZING_IO__DESCRIPTOR__HH__
#define   __NOVEMBERIZING_IO__DESCRIPTOR__HH__

#include <vector>
#include <functional>
#include <unistd.h>
#include <fcntl.h>

#include <novemberizing.hh>

#include <novemberizing/io.hh>

#include <novemberizing/concurrency/sync.hh>

namespace novemberizing { namespace io {

using namespace concurrency;

class Descriptor : public Sync
{
public:     class Map : public Sync
            {
            private:    std::vector<Descriptor *> __map;
            public:     Descriptor * get(int v);
            public:     void set(Descriptor * descriptor,std::function<void(Descriptor *)> f = nullptr);
            public:     void del(int v,std::function<void(Descriptor *)> f = nullptr);
            public:     void del(Descriptor * descriptor);
            public:     Map(type::size reserved = 1024);
            public:     virtual ~Map(void);
            };
public:     static Descriptor::Map alives;
protected:  int __descriptor;
protected:  type::uint32 __registered;
public:     virtual bool nonblock(bool v);
public:     inline void registered(type::uint32 v);
public:     inline type::uint32 registered(void) const;
public:     inline bool alive(void) const;
public:     inline int v(void) const;
public:     virtual bool should(EventType type) const = 0;
public:     virtual int open(void) = 0;
public:     virtual type::int64 read(void) = 0;
public:     virtual type::int64 write(void) = 0;
public:     virtual type::int64 write(const type::byte * bytes,type::size length) = 0;
public:     virtual int close(void) = 0;
public:     Descriptor(void);
public:     virtual ~Descriptor(void);
};

} }


#include <novemberizing/io/descriptor.inline.hh>

#endif // __NOVEMBERIZING_IO__DESCRIPTOR__HH__
