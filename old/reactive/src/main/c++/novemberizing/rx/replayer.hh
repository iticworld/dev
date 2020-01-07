#ifndef   __NOVEMBERIZING_RX__REPLAYER__HH__
#define   __NOVEMBERIZING_RX__REPLAYER__HH__

#include <novemberizing/ds/concurrent.list.hh>

#include <novemberizing/rx/play.hh>
#include <novemberizing/rx/emittable.hh>

namespace novemberizing { namespace rx {

using namespace ds;
using namespace concurrency;

template <class T> class Observer;

template <class T>
class Replayer : public Emittable<T>
{
public:     class Replay : public Play<T>
            {
            private:    T __item;
            public:     virtual void on(Observer<T> * observer);
            public:     Replay(const T & item);
            public:     virtual ~Replay(void);
            public:     class Error : public Play<T>
                        {
                        private:    Throwable __exception;
                        public:     virtual void on(Observer<T> * observer);
                        public:     Error(const Throwable & e);
                        public:     virtual ~Error(void);
                        };
            public:     class Complete : public Play<T>
                        {
                        public:     virtual void on(Observer<T> * observer);
                        public:     Complete(void);
                        public:     virtual ~Complete(void);
                        };
            };
private:    type::size __limit;
private:    ConcurrentList<Play<T> *, Sync> __replays;
public:     virtual void emit(const T & item);
public:     virtual void error(const Throwable & exception);
public:     virtual void complete(void);
public:     void on(Observer<T> * observer);
public:     void limit(type::size v);
public:     Replayer(type::size limit = 0);
public:     virtual ~Replayer(void);
public:     friend class Observer<T>;
};

} }

#include <novemberizing/rx/replayer.inline.hh>
#include <novemberizing/rx/replayer.replay.inline.hh>
#include <novemberizing/rx/replayer.replay.error.inline.hh>
#include <novemberizing/rx/replayer.replay.complete.inline.hh>

#endif // __NOVEMBERIZING_RX__REPLAYER__HH__
