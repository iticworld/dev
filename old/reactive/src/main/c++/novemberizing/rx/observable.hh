#ifndef   __NOVEMBERIZING_RX__OBSERVABLE__HH__
#define   __NOVEMBERIZING_RX__OBSERVABLE__HH__

#include <initializer_list>

#include <novemberizing/ds.hh>

#include <novemberizing/ds/concurrent.linked.set.hh>

#include <novemberizing/rx/emittable.hh>
#include <novemberizing/rx/subscribable.hh>
#include <novemberizing/rx/replayer.hh>
#include <novemberizing/rx/task.hh>
#include <novemberizing/rx/scheduler.hh>

namespace novemberizing { namespace rx {

using namespace ds;

template <class T>
class Observable : public Emittable<T>, public Subscribable<T>, public Sync
{
public:     static Observable<T> * Just(void);
public:     static Observable<T> * Just(int argc, const T * argv);
public:     static Observable<T> * Just(const T & v);
public:     static Observable<T> * Just(const T && v);
public:     static Observable<T> * Just(std::initializer_list<T> list);
private:    class Emit : public Task
            {
            private:    Observable<T> * __observable;
            private:    T __value;
            private:    Replayer<T> __replayers;
            public:     const T & in(void) const;
            public:     virtual void execute(void);
            public:     Emit(Observable<T> * observable,const T & v);
            public:     virtual ~Emit(void);
            };
private:    class Error : public Task
            {
            private:    Observable<T> * __observable;
            private:    Throwable __exception;
            private:    Replayer<T> __replayers;
            public:     const Throwable & exception(void) const;
            public:     virtual void execute(void);
            public:     Error(Observable<T> * observable,const Throwable & v);
            public:     virtual ~Error(void);
            };
private:    class Complete : public Task
            {
            private:    Observable<T> * __observable;
            private:    Replayer<T> __replayers;
            public:     virtual void execute(void);
            public:     Complete(Observable<T> * observable);
            public:     virtual ~Complete(void);
            };
private:    ConcurrentLinkedSet<Observer<T> *> __observers;
private:    Replayer<T> __replayer;
private:    Scheduler * __observableOn;
private:    void __emit(const T & item);
private:    void __error(const Throwable & e);
private:    void __complete(void);
protected:  virtual void emit(const T & item);
protected:  virtual void error(const Throwable & exception);
protected:  virtual void complete(void);
public:     virtual Observable<T> * subscribe(Observer<T> * observer);
public:     virtual Observable<T> * unsubscribe(Observer<T> * observer);
public:     virtual Observable<T> * unsubscribe(void);
public:     Observable(void);
public:     virtual ~Observable(void);
public:     friend class Observer<T>;
};

} }

#include <novemberizing/rx/observable.inline.hh>
#include <novemberizing/rx/observable.emit.inline.hh>
#include <novemberizing/rx/observable.error.inline.hh>
#include <novemberizing/rx/observable.complete.inline.hh>

#endif // __NOVEMBERIZING_RX__OBSERVABLE__HH__
