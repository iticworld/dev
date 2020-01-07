#ifndef   __NOVEMBERIZING_UTIL__CLI__HH__
#define   __NOVEMBERIZING_UTIL__CLI__HH__

#include <string>
#include <map>
#include <functional>
#include <list>

#include <novemberizing.hh>
#include <novemberizing/util/log.hh>

namespace novemberizing { namespace util {

class CommandLine
{
private:    std::map<std::string, std::function<int(const std::list<std::string> &)> > __map;
public:     CommandLine & add(const std::string & key, std::function<int(const std::list<std::string> &)> f);
public:     CommandLine & del(const std::string & key);
public:     int call(const std::string & line);
public:     CommandLine(void);
public:     virtual ~CommandLine(void);
};

} }

#endif // __NOVEMBERIZING_UTIL__CLI__HH__
