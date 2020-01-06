#include "file.hh"

namespace novemberizing { namespace util { namespace loggers {

File::File(const std::string & path,const std::string & name) : __path(path), __name(name)
{

}

File::File(const std::string & path,std::string && name) : __path(path), __name(name)
{

}

File::File(std::string && path,const std::string & name) : __path(path), __name(name)
{

}

File::File(std::string && path,std::string && name) : __path(path), __name(name)
{

}

File::~File(void)
{

}

void File::__write(Log::Type type, Log::Time & current, const char * msg,type::uint32 len)
{
    char full[1024];
    snprintf(full, 1024, "%s/%s.%s.%04d.%02d.%02d.log",
                            __path.c_str(),
                            __name.c_str(),
                            Log::toString(type),
                            current.year(),
                            current.month(),
                            current.day());
    FILE * fp = fopen(full,"wb");
    if(fp!=nullptr)
    {
        fwrite(msg,sizeof(char),len,fp);
        fclose(fp);
    }
}

// class File : public Logger
// {
// private:    std::string __path;
// private:    std::string __name;
// protected:	virtual void __write(Log::Type type, Log::Time & current, const char * msg,type::uint32 len);
// public:		File(const std::string & path,const std::string & name);
// public:		File(const std::string & path,std::string && name);
// public:		File(std::string && path,const std::string & name);
// public:		File(std::string && path,std::string && name);
// public:		virtual ~File(void);
// };

} } }
