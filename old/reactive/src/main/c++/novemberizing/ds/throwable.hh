#ifndef   __NOVEMBERIZING_DS__THROWABLE__HH__
#define   __NOVEMBERIZING_DS__THROWABLE__HH__

#include <string>
#include <ostream>

namespace novemberizing { namespace ds {

class Throwable
{
protected:  std::string __msg;
public:     const std::string & msg(void) const;
public:     Throwable(void);
public:     Throwable(const std::string & v);
public:     Throwable(const std::string && v);
public:     virtual ~Throwable(void);
};

std::ostream & operator<<(std::ostream & o, const Throwable & e);

} }

#endif // __NOVEMBERIZING_DS__THROWABLE__HH__
