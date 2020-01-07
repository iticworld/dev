#ifndef   __NOVEMBERIZING_RX__OBSERVABLE__INLINE__HH__
#define   __NOVEMBERIZING_RX__OBSERVABLE__INLINE__HH__

#include <novemberizing/rx/observable.hh>

namespace novemberizing { namespace rx {

template <class T>
Observable<T> * Observable<T>::Just(void){
    Observable<T> * observable = new Observable();
    synchronized(observable,{
        observable->__replayer.limit(1);
        observable->__replayer.complete();
    });
    return observable;
}

template <class T>
Observable<T> * Observable<T>::Just(int argc, const T * argv)
{
    Observable<T> * observable = new Observable();
    synchronized(observable, {
        observable->__replayer.limit(argc+1);
        for(int i=0;i<argc;i++){
            observable->__replayer.emit(argv[i]);
        }
        observable->__replayer.complete();
    });
    return observable;
}

template <class T>
Observable<T> * Observable<T>::Just(const T & v)
{
    Observable<T> * observable = new Observable();
    synchronized(observable, {
        observable->__replayer.limit(2);
        observable->__replayer.emit(v);
        observable->__replayer.complete();
    });
    return observable;
}

template <class T>
Observable<T> * Observable<T>::Just(const T && v)
{
    Observable<T> * observable = new Observable();
    synchronized(&observable,{
        observable->__replayer.limit(2);
        observable->__replayer.emit(v);
        observable->__replayer.complete();
    });
    return observable;
}

template <class T>
Observable<T> * Observable<T>::Just(std::initializer_list<T> list)
{
    Observable<T> * observable = new Observable();
    synchronized(observable, {
        observable->__replayer.limit(list.size() + 1);
        foreach(list.begin(),list.end(),{
            observable->__replayer.emit(*it);
        });
        observable->__replayer.complete();
    });
    return observable;
}

template <class T>
Observable<T>::Observable(void) : __observableOn(Scheduler::Get())
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Observable<T>::~Observable(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
void Observable<T>::__emit(const T & item)
{
    FUNCTION_START("");
    synchronized(&__observers,{
        foreach(__observers.begin(),__observers.end(), {
            Observer<T> * observer = *it;
            if(observer!=nullptr){
                observer->onNext(item);
            }
        });
    });
    FUNCTION_END("");
}

template <class T>
void Observable<T>::__error(const Throwable & e)
{
    FUNCTION_START("");
    synchronized(&__observers,{
        foreach(__observers.begin(),__observers.end(), {
            Observer<T> * observer = *it;
            if(observer!=nullptr){
                observer->onError(e);
            }
        });
    });
    FUNCTION_END("");
}

template <class T>
void Observable<T>::__complete(void)
{
    FUNCTION_START("");
    synchronized(&__observers,{
        foreach(__observers.begin(),__observers.end(), {
            Observer<T> * observer = *it;
            if(observer!=nullptr){
                observer->onComplete();
            }
        });
    });
    FUNCTION_END("");
}

template <class T>
Observable<T> * Observable<T>::subscribe(Observer<T> * observer)
{
    FUNCTION_START("");
    if(observer!=nullptr)
    {
        synchronized(&__observers,if(__observers.add(observer)){
            /**
             * @todo check deadlock
             */
            observer->onSubscribe(this);
            __replayer.on(observer);
        } else {
            WARNING_LOG("fail to __observers.add(...)");
        });
    }
    else
    {
        WARNING_LOG("observer==nullptr");
    }

    FUNCTION_END("");
    return this;
}

template <class T>
Observable<T> * Observable<T>::unsubscribe(Observer<T> * observer)
{
    FUNCTION_START("");
    if(observer!=nullptr)
    {
        synchronized(&__observers, if(__observers.del(observer)){
            observer->onUnsubscribe(this);
        } else {
            WARNING_LOG("fail to __observers.del(...)");
        });
    }
    else
    {
        WARNING_LOG("observer==nullptr");
    }
    FUNCTION_END("");
    return this;
}

template <class T>
Observable<T> * Observable<T>::unsubscribe(void)
{
    FUNCTION_START("");

    synchronized(&__observers, __observers.clear());

    FUNCTION_END("");
    return this;
}

template <class T>
void Observable<T>::emit(const T & item)
{
    /** always register scheduler */
    __observableOn->dispatch(new typename Observable<T>::Emit(this, item));
}

template <class T>
void Observable<T>::error(const Throwable & exception)
{

}

template <class T>
void Observable<T>::complete(void)
{

}

} }

#endif // __NOVEMBERIZING_RX__OBSERVABLE__INLINE__HH__
