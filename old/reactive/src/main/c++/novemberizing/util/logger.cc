#include <novemberizing/util/logger.hh>

namespace novemberizing { namespace util {

void Logger::write(Log::Type type, Log::Time & current, const char * msg,type::uint32 len)
{
	__write(type, current, msg, len);
}

Logger::Logger(void){}
Logger::~Logger(void){}

} }
