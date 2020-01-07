#ifndef   __NOVEMBERIZING_RX_OBSERVABLES__JUST__HH__
#define   __NOVEMBERIZING_RX_OBSERVABLES__JUST__HH__

namespace novemberizing { namespace rx { namespace observables {

template <class T>
class Just : public Observable<T>
{
protected:  virtual void emit(const T & item);
protected:  virtual void error(const Throwable & exception);
protected:  virtual void complete(void);
public:     Just(void);
public:     virtual ~Just(void);
};

} } }

#endif // __NOVEMBERIZING_RX_OBSERVABLES__JUST__HH__
