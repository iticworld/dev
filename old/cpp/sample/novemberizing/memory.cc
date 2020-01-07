#include <novemberizing/memory.hh>

using namespace novemberizing;

template <typename T>
void check()
{
    T * p = memory::allocate<T>(1024);  // NOLINT
    p = memory::allocate<T>(p, 4096);
    T * source = memory::allocate<T>(16);  // NOLINT
    memory::copy<T>(p, source, 16);
    memory::move<T>(p, p, 4);
    memory::deallocate<T>(p);
    memory::deallocate<T>(source);
}

template <typename T>
void check(const T & o)
{
    T * p = memory::allocate<T>(1024);  // NOLINT
    p = memory::allocate<T>(p, 4096);
    T * source = memory::allocate<T>(16);  // NOLINT
    memory::copy<T>(p, source, 16);
    memory::move<T>(p, p, 4);
    memory::fill<T>(p, o, 10);
    memory::deallocate<T>(p);
    memory::deallocate<T>(source);
}

int main(int argc, char ** argv)
{
    check<void>();
    check<char>();
    check<signed char>();
    check<unsigned char>();
    check<short>();
    check<unsigned short>();
    check<int>();
    check<unsigned int>();
    check<long>();
    check<unsigned long>();
    check<long long>();
    check<unsigned long long>();

    check<char>(0);
    check<signed char>(0);
    check<unsigned char>(0);
    check<short>(0);
    check<unsigned short>(0);
    check<int>(0);
    check<unsigned int>(0);
    check<long>(0);
    check<unsigned long>(0);
    check<long long>(0);
    check<unsigned long long>(0);

    char buf[16];
    memory::set(buf, 0, 16);

    memory::move<void>(buf, &buf[4], 1);
    memory::fill<char>(buf, 'c', 4);
    memory::fill<signed char>((signed char *) buf, 'c', 4);
    memory::fill<unsigned char>((unsigned char *)buf, 'c', 4);


    return 0;
}
