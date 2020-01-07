#ifndef   __NOVEMBERIZING_DS__CYCLABLE__HH__
#define   __NOVEMBERIZING_DS__CYCLABLE__HH__

#include <novemberizing/util/log.hh>

namespace novemberizing { namespace ds {

using namespace util;

class Cyclable
{
public:     virtual void onecycle(void) = 0;
public:     Cyclable(void);
public:     virtual ~Cyclable(void);
};

} }

#endif // __NOVEMBERIZING_DS__CYCLABLE__HH__
