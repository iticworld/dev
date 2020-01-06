/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 17.
 */

#include <novemberizing.hh>
#include <novemberizing/linked/list.hh>

using namespace novemberizing;

static void hex(const bytes & o)
{
    char str[32];
    for(uint64 i = 0; i < o.size(); i++)
    {
        if(i % 16 == 0)
        {
            printf("| %08X | ", (unsigned int) i);
        }
        byte c = o[i];
        printf("%02X ", c);
        str[i % 16] = (32 <= c && c<=126 ? c : '.');
        str[i % 16 + 1] = 0;
        if(i % 16 == 15)
        {
            printf("| %s |\n", str);
        }
        else if(i + 1 == o.size())
        {
            printf("%-*c| %-16s |\n", (int)(3 * (15 - (i % 15))), ' ', str);
        }
    }
}

class data
{
private:    uint32 __length;
private:    uint32 __original;
private:    uint32 __address;
public:     uint32 length() const { return __length; }
public:     uint32 address() const { return __address; }
public:     uint32 original() const { return __original; }
public:     void print() const
            {
                printf("{ length: %d, original: %d, address: %08X }\n",__length, __original, __address);
            }
public:     bool operator==(const data & y)
            {
                return __length == y.__length && __original == y.__original && __address == y.__address;
            }
public:     data & operator=(const data & o)
            {
                if(&o != this)
                {
                    __length = o.__length;
                    __original = o.__original;
                    __address = o.__address;
                }
                return *this;
            }
public:     data & operator=(data && o) noexcept
            {
                if(&o != this)
                {
                    __length = o.__length;
                    __original = o.__original;
                    __address = o.__address;

                    o.__length = 0;
                    o.__original = 0;
                    o.__address = 0;
                }
                return *this;
            }
public:     data(uint32 length, uint32 original, uint32 address) : __length(length), __original(original), __address(address) {}
public:     data() : __length(0), __original(0), __address(0) {}
public:     data(const data & o) : __length(o.__length), __original(o.__original), __address(o.__address) {}
public:     data(data && o) noexcept  : __length(o.__length), __original(o.__original), __address(o.__address)
            {
                o.__length = 0;
                o.__original = 0;
                o.__address = 0;
            }
public:     virtual ~data()
            {
                __length = 0;
                __original = 0;
                __address = 0;
            }
};



int main(int argc, char ** argv)
{
    if(argc == 2)
    {
        bytes b;
        FILE * fp = fopen(argv[1], "r+b");
        if(fp)
        {
            byte buffer[4096];
            while(!feof(fp))
            {
                ssize_t n = fread(buffer, sizeof(byte), 4096, fp);
                if(n > 0)
                {
                    b.append(buffer, (uint64) n);
                }
            }
            fclose(fp);
            /** check header */
            if(b[0] != 'L' || b[1] != 'S' || b[2] != '1')
            {
                printf("\"%s\" is not ls11 file\n", argv[1]);
                return -1;
            }
            if(b[3] != '0' && b[3] != '1' && b[3] != '2')
            {
                printf("\"%s\" is not ls11 file\n", argv[1]);
                return -1;
            }
            for(uint64 i = 4; i < 16; i++)
            {
                if(b[i] != 0)
                {
                    printf("\"%s\" is not ls11 file\n", argv[1]);
                    return -1;
                }
            }
            bytes dictionary = bytes::sub(b, 0x10, 0x100);
            hex(dictionary);
            uint32 v = 0;
            uint32 start = 0x110;
            linked::list<data> items;
            do {
                v = bytes::to::uinteger32(b, start, true);
                if(v != 0)
                {
                    uint32 length = v;
                    start += 4;
                    uint32 original = bytes::to::uinteger32(b, start, true);
                    start += 4;
                    uint32 address = bytes::to::uinteger32(b, start, true);
                    start += 4;
                    items.add(data(length, original, address));
                    printf("length: %d, original: %d, address: 0x%08X\n", length, original, address);
                }
                else
                {
                    start += 4;
                }
            } while(v != 0);
            printf("start: 0x%08X\n", start);
            items.each([&b, &dictionary](const data & o){

                bytes original = bytes::sub(b, o.address(), o.length());
                hex(original);
                o.print();

            });
        }
        else
        {
            printf("fail to open file : %d\n", errno);
            return -1;
        }
    }
    else
    {
        printf("/usr/local/bin/novemberizing/ls11 \"path\"\n");
        return -1;
    }
    return 0;
}

