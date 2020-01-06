#ifndef   __NOVEMBERIZING_DS__FUNC__HH__
#define   __NOVEMBERIZING_DS__FUNC__HH__

namespace novemberizing { namespace ds {

template <class A, class Z>
class Func
{
public:     typedef Z (*F)(A);
public:     virtual Z operator()(A first) = 0;
public:     Func(void);
public:     virtual ~Func(void);
};

} }

#include <novemberizing/ds/func.inline.hh>

#endif // __NOVEMBERIZING_DS__FUNC__HH__
