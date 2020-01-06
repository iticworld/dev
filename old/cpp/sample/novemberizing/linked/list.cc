#include <novemberizing/linked/list.hh>
#include <novemberizing/random.hh>

using namespace novemberizing;

int main(int argc, char ** argv)
{
    try
    {
        linked::list<type::int32> x;
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
        for(type::int32 i = 0; i < 4; i++)
        {
            if(!x.add(random::get<type::int32>(10)))
            {
                throw exception();  // NOLINT
            }
        }
        x.each([](const type::int32 & v){ printf("%d\n", v); });
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
        x.clear();
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
        for(type::int32 i = 0; i < 4; i++)
        {
            x.add(random::get<type::int32>(10), [](const type::int32 & v, bool result){
                if(!result)
                {
                    throw exception();  // NOLINT
                }
            });
        }
        x.each([](const type::int32 & v){ printf("%d\n", v); });
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
        x.clear([](type::int32 && v){ printf("clear: %d\n", v); });
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
        for(type::int32 i = 0; i < 8; i++)
        {
            x.add(random::get<type::int32>(10), [](const type::int32 & v, bool result){
                if(!result)
                {
                    throw exception();  // NOLINT
                }
            });
        }
        x.each([](const type::int32 & v){ printf("%d\n", v); });
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
        for(type::int32 i = 0; i < 4; i++)
        {
            if(x.exist(random::get<type::int32>(10)))
            {
                printf("exist\n");
            }
        }
        for(type::int32 i = 0; i < 4; i++)
        {
            x.exist(random::get<type::int32>(10), [](const type::int32 & v, bool result){
                printf("%d is %s\n", v, result ? "exist" : "not exist");
            });
        }
        for(type::int32 i = 0; i < 4; i++)
        {
            if(x.del(random::get<type::int32>(10)))
            {
                printf("del\n");
            }
        }
        for(type::int32 i = 0; i < 4; i++)
        {
            x.del(random::get<type::int32>(10), [](type::int32 && v, bool result){
                printf("%d is %s\n", v, result ? "deleted" : "not deleted");
            });
        }
        x.each([](const type::int32 & v){ printf("%d\n", v); });
        printf("empty: %s\n", x.empty() ? "true" : "false");
        printf("size: %ld\n", x.size());
        x.empty([](bool v){ printf("empty: %s\n", v ? "true" : "false"); });
        x.size([](type::size v){ printf("size: %ld\n",v); });
    }
    catch(...)
    {
        printf("throws\n");
        exit(0);
    }
    return 0;
}

