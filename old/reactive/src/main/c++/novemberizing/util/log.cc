#include <list>
#include <algorithm>

#include <novemberizing/util/log.hh>
#include <novemberizing/util/logger.hh>

namespace novemberizing { namespace util {

const char * Log::toString(Log::Type type)
{
	switch(type)
	{
	case Log::Error:		return "error";
	case Log::Warning:		return "warning";
	case Log::Caution:		return "caution";
	case Log::Notice:		return "notice";
	case Log::Information:	return "information";
	case Log::Flow:			return "flow";
	case Log::Debug:		return "debug";
	case Log::Verbose:		return "verbose";
	default:				return "unknown";
	}
	return "unknown";
}

Log::Log(void)
{
    __types = (Log::Error | Log::Warning | Log::Caution | Log::Notice | Log::Information);
}

Log::~Log(void)
{
	for(std::list<Logger *>::iterator it = __loggers.begin();it!=__loggers.end();it = __loggers.erase(it))
	{
		Logger * logger = *it;
		delete logger;
	}
}

void Log::write(Log::Type type, const char * file, type::uint32 line, const char * function, const char * format, ...)
{
	if(__types & type)
	{
		const type::uint32 size = 4096;
		char str[size];

		Log::Time current;
		int n = snprintf(	str,
							size,
							"%04u/%02u/%02u %02u:%02u:%02u.%09lu %s:%d %s %lu %s > ",
							current.year(),
							current.month(),
							current.day(),
							current.hour(),
							current.minute(),
							current.second(),
							current.nano(),
							file,
							line,
							function,
							::pthread_self(),
							toString(type));

		va_list ap;
		va_start(ap, format);
		n+=vsnprintf(&str[n],size-n-1,format,ap);
		va_end(ap);
		str[n] = '\n';
        str[n+1] = 0;
		if(__loggers.size()>0)
		{
			for(std::list<Logger *>::iterator it = __loggers.begin();it!=__loggers.end();it++)
			{
				Logger * logger = *it;
				logger->write(type, current, str, n);
			}
		}
		else
		{
			printf("%s",str);
		}
	}
}

Log & Log::disable(type::uint32 type)
{
	__types &= (~type);
	return *this;
}

Log & Log::enable(type::uint32 type)
{
	__types |= (type);
	return *this;
}

Log & Log::add(Logger * logger)
{
	if(logger!=nullptr)
	{
		if(std::find(__loggers.begin(),__loggers.end(),logger)==__loggers.end())
		{
			__loggers.push_back(logger);
		}
	}
	return *this;
}

Log & Log::del(Logger * logger)
{
	if(logger!=nullptr)
	{
		__loggers.erase(std::find(__loggers.begin(),__loggers.end(),logger));
	}
	return *this;
}

Log::Time::Time(void)
{
	struct timespec spec;
	if(::clock_gettime(CLOCK_REALTIME, &spec)==Success)
	{
		__nano = spec.tv_nsec;
		__timestamp = spec.tv_sec;
		struct tm tm;
		localtime_r(&__timestamp, &tm);
		__year = 1900 + tm.tm_year;
		__month = 1 + tm.tm_mon;
		__day = tm.tm_mday;
		__hour = tm.tm_hour;
		__minute = tm.tm_min;
		__second = tm.tm_sec;
	}
	else
	{
		printf("fail to ::clock_gettime(...) caused by %d\n",errno);
	}
}

Log::Time::~Time(void) {}

Log Log::o;

} }
