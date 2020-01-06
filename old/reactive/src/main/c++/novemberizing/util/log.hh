#ifndef   __NOVEMBERIZING_UTIL__LOG__HH__
#define   __NOVEMBERIZING_UTIL__LOG__HH__

#include <list>
#include <algorithm>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#include <novemberizing.hh>

namespace novemberizing { namespace util {

class Logger;

class Log
{
public:	    class Time
			{
			private:	type::uint32 __year;
			private:	type::uint32 __month;
			private:	type::uint32 __day;
			private:	type::uint32 __hour;
			private:	type::uint32 __minute;
			private:	type::uint32 __second;
			private:	type::nano __nano;
			private:	type::second __timestamp;
			public:		inline type::uint32 year(void) const { return __year; }
			public:		inline type::uint32 month(void) const { return __month; }
			public:		inline type::uint32 day(void) const { return __day; }
			public:		inline type::uint32 hour(void) const { return __hour; }
			public:		inline type::uint32 minute(void) const { return __minute; }
			public:		inline type::uint32 second(void) const { return __second; }
			public:		inline type::nano nano(void) const { return __nano; }
			public:		inline type::second timestamp(void) const { return __timestamp; }
			public:		Time(void);
			public:		virtual ~Time(void);
			};
public:		typedef enum __Type
			{
				Error = 0x00000001 <<  0,
				Warning = 0x00000001 <<  1,
				Caution = 0x00000001 <<  2,
				Notice = 0x00000001 <<  3,
				Information = 0x00000001 <<  4,
				Debug = 0x00000001 <<  5,
				Flow = 0x00000001 <<  6,
				Verbose = 0x00000001 <<  7,
			} Type;
public:		static const char * toString(Log::Type type);
public:		static Log o;
private:	type::uint32 __types;
private:	std::list<Logger *> __loggers;
public:		Log & disable(type::uint32 type);
public:		Log & enable(type::uint32 type);
public:		Log & add(Logger * logger);
public:		Log & del(Logger * logger);
public:		void write(Log::Type type, const char * file, type::uint32 line, const char * function, const char * format, ...);
private:	Log(void);
public:		virtual ~Log(void);
};

} }

#define FUNCTION_START(format,...)													\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Flow,				\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define FUNCTION_END(format,...)													\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Flow,				\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define ERROR_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Error,			\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define WARNING_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Warning,			\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define CAUTION_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Caution,			\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define NOTICE_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Notice,			\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define INFORMATION_LOG(format,...)													\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Information,		\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define FLOW_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Flow,				\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define DEBUG_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Debug,			\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)

#define VERBOSE_LOG(format,...)														\
	novemberizing::util::Log::o.write(	novemberizing::util::Log::Verbose,			\
										__FILE__,									\
										__LINE__,									\
										__func__,									\
										format,										\
										##__VA_ARGS__)


#endif // __NOVEMBERIZING_UTIL__LOG__HH__
