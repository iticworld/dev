#include <novemberizing/bytes.hh>
#include <novemberizing/string.hh>

using namespace novemberizing;

#include <cstdio>

int main(int argc, char ** argv)
{
    try
    {
        bytes o;

        printf("capacity: %ld\n", o.capacity());
        printf("size: %ld\n", o.size());
    }
    catch(...)
    {

    }

    try
    {
        bytes o((type::byte *) "hello world", 11);
        o.append(0);
        printf("%s\n", o.v(6));
        printf("%s\n", o.v());
        printf("%c\n", o.at(1));
        printf("%c\n", o.at(2));
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.append(0);
        bytes y;
        y.assign(x);
        printf("%s\n", y.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.append(0);
        bytes y;
        y.assign(x, 6);
        y.append(0);
        printf("%s\n", y.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.append(0);
        bytes y;
        y.assign(x, 6, 3);
        y.append(0);
        printf("%s\n", y.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x;
        x.assign((type::byte *) "hello world", 11);
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x;
        x.assign('c', 11);
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        bytes y((type::byte *) "hi", 2);
        x.append(0);
        x.replace(0, 5, y);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        bytes y((type::byte *) "hi novemberizing", string::length("hi novemberizing"));
        x.append(0);
        x.replace(0, 5, y, 3);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        bytes y((type::byte *) "hi novemberizing", string::length("hi novemberizing"));
        x.append(0);
        x.replace(0, 5, y, 3, 3);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        bytes y((type::byte *) "hi novemberizing", string::length("hi novemberizing"));
        x.append(0);
        x.replace(0, 5, move(y));
        printf("%s\n", x.v());
        printf("%ld\n", y.size());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.append(0);
        x.replace(0, 5, (type::byte *) "novemberizing", 13);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.append(0);
        x.replace(0, 6, '@');
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.append(0);
        x.replace(0, 6, '^', 2);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.erase();
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x((type::byte *) "hello world", 11);
        x.erase(6);
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x(type::uint16(16));
        printf("%d\n", *((type::uint16 *) x.v()));
    }
    catch(...)
    {

    }

    try
    {
        bytes x(type::uint32(32));
        printf("%d\n", *((type::uint32 *) x.v()));
    }
    catch(...)
    {

    }

    try
    {
        bytes x(type::uint64(64));
        printf("%ld\n", *((type::uint64 *) x.v()));
    }
    catch(...)
    {

    }


    try
    {
        bytes x(type::int16(-16));
        printf("%d\n", *((type::int16 *) x.v()));
    }
    catch(...)
    {

    }

    try
    {
        bytes x(type::int32(-32));
        printf("%d\n", *((type::int32 *) x.v()));
    }
    catch(...)
    {

    }

    try
    {
        bytes x(type::int64(-64));
        printf("%ld\n", *((type::int64 *) x.v()));
        x.clear();
        printf("%ld\n", x.size());
    }
    catch(...)
    {

    }

    try
    {
        bytes y((type::byte *)("hello world"), 11);
        bytes x(y, 6);
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes y((type::byte *)("hello world"), 11);
        bytes x(y, 6, 3);
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        bytes x(type::byte('!'));
        x.append(0);
        printf("%s\n", x.v());
        printf("%ld\n", x.size());
    }
    catch(...)
    {

    }

    try
    {
        bytes x('!', 5);
        x.append(0);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }


    return 0;
}
