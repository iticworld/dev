#ifndef   __NOVEMBERIZING_DS__ON__HH__
#define   __NOVEMBERIZING_DS__ON__HH__

namespace novemberizing { namespace ds {

template <class A>
class On
{
public:     virtual void operator()(A first) = 0;
public:     On(void);
public:     virtual ~On(void);
};

} }

#endif // __NOVEMBERIZING_DS__ON__HH__
