#include "command.line.hh"

#include <iostream>

namespace novemberizing { namespace util {

CommandLine::CommandLine(void)
{

}

CommandLine::~CommandLine(void)
{

}

CommandLine & CommandLine::add(const std::string & key, std::function<int(const std::list<std::string> &)> f)
{
    __map.insert(std::pair<std::string, std::function<int(const std::list<std::string> &)> >(key, f));
    return *this;
}

CommandLine & CommandLine::del(const std::string & key)
{
    __map.erase(key);
    return *this;
}

int CommandLine::call(const std::string & line)
{
    int ret = Fail;
    if(line.length()>0)
    {
        std::list<std::string> spilts;
        type::size front = 0;
        type::size back = 0;
        do {
            front = line.find_first_not_of("\r\n\t ",front);
            if(front!=std::string::npos)
            {
                back = line.find_first_of("\r\n\t ", front + 1);
                if(back!=std::string::npos)
                {
                    spilts.push_back(line.substr(front, back - front));
                    front = back + 1;
                }
                else
                {
                    // WARNING_LOG("back==std::string::npos");
                }
            }
            else
            {
                // WARNING_LOG("front==std::string::npos");
            }
        } while(front!=std::string::npos && back!=std::string::npos);
        if(spilts.size()>0)
        {
            std::map<std::string, std::function<int(const std::list<std::string> &)> >::iterator found = __map.find(spilts.front());
            if(found!=__map.end())
            {
                if(found->second!=nullptr)
                {
                    ret = found->second(spilts);
                }
                else
                {
                    ERROR_LOG("found->second==nullptr");
                }
            }
            else
            {
                ERROR_LOG("found==__map.end()");
            }
        }
        else
        {
            ERROR_LOG("spilts.size()==0");
        }
        // for(std::list<std::string>::iterator it = spilts.begin();it!=spilts.end();it++)
        // {
        //     std::cout<<*it<<":"<<std::endl;
        // }
    }
    else
    {
        ERROR_LOG("line.length()==0");
    }
    return ret;
}

} }
