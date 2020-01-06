#ifndef   __NOVEMBERIZING_UTIL_LOGGERS__FILE__HH__
#define   __NOVEMBERIZING_UTIL_LOGGERS__FILE__HH__

#include <novemberizing/util/logger.hh>

namespace novemberizing { namespace util { namespace loggers {

class File : public Logger
{
private:    std::string __path;
private:    std::string __name;
protected:	virtual void __write(Log::Type type, Log::Time & current, const char * msg,type::uint32 len);
public:		File(const std::string & path,const std::string & name);
public:		File(const std::string & path,std::string && name);
public:		File(std::string && path,const std::string & name);
public:		File(std::string && path,std::string && name);
public:		virtual ~File(void);
};

} } }

#endif // __NOVEMBERIZING_UTIL_LOGGERS__FILE__HH__
