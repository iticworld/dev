#ifndef   __NOVEMBERIZING_RX__REPLAYER__INLINE__HH__
#define   __NOVEMBERIZING_RX__REPLAYER__INLINE__HH__

namespace novemberizing { namespace rx {

template <class T>
Replayer<T>::Replayer(type::size limit) : __limit(limit)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

template <class T>
Replayer<T>::~Replayer(void)
{
    FUNCTION_START("");
    __replays.lock();
    for(typename ConcurrentList<Play<T> *, Sync>::iterator it = __replays.begin();it!=__replays.end();it = __replays.erase(it)){
        Play<T> * play = *it;
        if(play!=nullptr)
        {
            delete play;
        }
    }
    __replays.unlock();
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::on(Observer<T> * observer)
{
    FUNCTION_START("");
    if(observer!=nullptr)
    {
        __replays.lock();
        for(typename ConcurrentList<Play<T> *, Sync>::iterator it = __replays.begin();it!=__replays.end();it++){
            Play<T> * play = *it;
            if(play!=nullptr)
            {
                play->on(observer);
            }
        }
        __replays.unlock();
    }
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::emit(const T & item)
{
    FUNCTION_START("");
    synchronized(&__replays,{
        __replays.push(new typename Replayer<T>::Replay(item));
        while(__limit<__replays.size())
        {
            __replays.pop([](Play<T> * play){
                if(play!=nullptr){
                    delete play;
                }
            });
        }
    });
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::error(const Throwable & e)
{
    FUNCTION_START("");
    synchronized(&__replays,{
        __replays.push(new typename Replayer<T>::Replay::Error(e));
        while(__limit<__replays.size())
        {
            __replays.pop([](Play<T> * play){
                if(play!=nullptr){
                    delete play;
                }
            });
        }
    });
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::complete(void)
{
    FUNCTION_START("");
    synchronized(&__replays,{
        __replays.push(new typename Replayer<T>::Replay::Complete());
        while(__limit<__replays.size())
        {
            __replays.pop([](Play<T> * play){
                if(play!=nullptr){
                    delete play;
                }
            });
        }
    });
    FUNCTION_END("");
}

template <class T>
void Replayer<T>::limit(type::size v)
{
    FUNCTION_START("");
    synchronized(&__replays,{
        __limit = v;
        while(__limit<__replays.size())
        {
            __replays.pop([](Play<T> * play){
                if(play!=nullptr){
                    delete play;
                }
            });
        }
    });
    FUNCTION_END("");
}

} }

#endif // __NOVEMBERIZING_RX__REPLAYER__INLINE__HH__
