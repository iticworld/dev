#include <novemberizing.hh>

using namespace novemberizing;

#include <cstdio>

int main(int argc, char ** argv)
{
    printf("type::int8: %ld\n", sizeof(type::int8));
    printf("type::int16: %ld\n", sizeof(type::int16));
    printf("type::int32: %ld\n", sizeof(type::int32));
    printf("type::int64: %ld\n", sizeof(type::int64));
    printf("type::uint8: %ld\n", sizeof(type::uint8));
    printf("type::uint16: %ld\n", sizeof(type::uint16));
    printf("type::uint32: %ld\n", sizeof(type::uint32));
    printf("type::uint64: %ld\n", sizeof(type::uint64));
    printf("type::byte: %ld\n", sizeof(type::byte));
    printf("type::character: %ld\n", sizeof(type::character));
    printf("type::pointer: %ld\n", sizeof(type::pointer));
    printf("type::size: %ld\n", sizeof(type::size));
    return 0;
}

