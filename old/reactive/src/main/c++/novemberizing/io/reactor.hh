#ifndef   __NOVEMBERIZING_IO__REACTOR__HH__
#define   __NOVEMBERIZING_IO__REACTOR__HH__

#include <sys/epoll.h>
#include <unistd.h>

#include <novemberizing/util/log.hh>

#include <novemberizing/ds.hh>
#include <novemberizing/ds/cyclable.hh>
#include <novemberizing/ds/concurrent.set.hh>

#include <novemberizing/io.hh>
#include <novemberizing/io/descriptor.hh>

namespace novemberizing { namespace io {

using namespace util;
using namespace ds;

class Reactor : public Cyclable
{
public:     static const int DefaultDescriptorSize = 1024;
public:     static const int DefaultTimeout = 10;
private:    ConcurrentSet<Descriptor *> __descriptors;
private:    int __descriptor;
private:    int __max;
private:    int __reserved;
private:    int __timeout;
private:    struct epoll_event * __events;
public:     virtual int add(Descriptor * descriptor);
public:     virtual int del(Descriptor * descriptor);
public:     virtual int mod(Descriptor * descriptor);
public:     virtual void onecycle(void);
private:    virtual void initialize(void);
public:     Reactor(void);
public:     virtual ~Reactor(void);
};

} }

#endif // __NOVEMBERIZING_IO__REACTOR__HH__
