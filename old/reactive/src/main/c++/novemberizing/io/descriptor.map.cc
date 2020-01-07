#include "descriptor.hh"

namespace novemberizing { namespace io {

Descriptor::Map::Map(type::size reserved)
{
    FUNCTION_START("");
    __map.resize(reserved);
    FUNCTION_END("");
}

Descriptor::Map::~Map(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Descriptor * Descriptor::Map::get(int v)
{
    FUNCTION_START("");
    Descriptor * descriptor = nullptr;
    if(0<=v && (unsigned int)v < __map.size())
    {
        descriptor = __map[v];
    }
    FUNCTION_END("");
    return descriptor;
}

void Descriptor::Map::set(Descriptor * descriptor,std::function<void(Descriptor *)> f)
{
    FUNCTION_START("");
    if(descriptor!=nullptr)
    {
        if(0<=descriptor->v())
        {
            if(__map.size()<=(unsigned int)descriptor->v())
            {
                __map.resize(descriptor->v()+1);
            }
            if(__map[descriptor->v()]!=nullptr && __map[descriptor->v()]!=descriptor)
            {
                if(f!=nullptr)
                {
                    f(__map[descriptor->v()]);
                }
                else
                {
                    delete __map[descriptor->v()];
                }
            }
            __map[descriptor->v()] = descriptor;
        }
        else
        {
            CAUTION_LOG("descriptor->v()<0");
        }
    }
    else
    {
        CAUTION_LOG("descriptor==nullptr");
    }
    FUNCTION_END("");
}

void Descriptor::Map::del(int v,std::function<void(Descriptor *)> f)
{
    FUNCTION_START("");
    if(0<=v && (unsigned int) v < __map.size())
    {
        if(__map[v]!=nullptr)
        {
            if(f!=nullptr)
            {
                f(__map[v]);
            }
            else
            {
                delete __map[v];
            }
            __map[v] = nullptr;
        }
    }
    FUNCTION_END("");
}

void Descriptor::Map::del(Descriptor * descriptor)
{
    FUNCTION_START("");
    if(descriptor!=nullptr)
    {
        if(0<=descriptor->v() && (unsigned int) descriptor->v() <__map.size())
        {
            if(__map[descriptor->v()]==descriptor)
            {
                __map[descriptor->v()] = nullptr;
            }
            else
            {
                NOTICE_LOG("__map[descriptor->v()]!=nullptr");
            }
        }
    }
    FUNCTION_END("");
}

} }
