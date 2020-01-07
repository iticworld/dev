#include <novemberizing/string.hh>

#include <cstdio>

using namespace novemberizing;

int main(int argc, char ** argv)
{
    try
    {
        string s = string::format("%s", "hello world");
        printf("%s\n", s.v());
    }
    catch(...)
    {

    }

    try
    {
        printf("%s\n", string::different("hello", "world") ? "true" : "false");
    }
    catch(...)
    {

    }

    try
    {
        printf("%s\n", string::equal("hello", "world") ? "true" : "false");
    }
    catch(...)
    {

    }


    try
    {
        string s = string::format("%s", "hello world");
        printf("%lu\n", s.capacity());
    }
    catch(...)
    {

    }

    try
    {
        string s = string::format("%s", "hello world");
        printf("%lu\n", s.size());
    }
    catch(...)
    {

    }

    try
    {
        const string x("hello");
        string y;
        y.assign(x, 3);
        printf("%s\n", y.v());
    }
    catch(...)
    {

    }

    try
    {
        const string x("world");
        string y;
        y.assign(x, 1, 3);
        printf("%s\n", y.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello");
        string y;
        y.assign(move(x));
        printf("%s\n", y.v());
    }
    catch(...)
    {

    }

    try
    {
        string x;
        x.assign("hello world", 8);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x;
        x.assign('c', 5);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.insert(5, " i");
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.erase();
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.erase(5);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string y("novemberizing.github.io!");
        string x("hello world");
        x.replace(6, 5, y);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string y("novemberizing.github.io!");
        string x("hello world");
        x.replace(6, 5, y, 14);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string y("novemberizing.github.io!");
        string x("hello world");
        x.replace(6, 5, y, 14, 6);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string y("novemberizing.github.io!");
        string x("hello world");
        x.replace(6, 5, move(y));
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.replace(6, 5, "novemberizing.github.io!");
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.replace(6, 5, "novemberizing.github.io!", 13);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.replace(5, 6, '!');
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }
    try
    {
        string x("hello world");
        x.replace(5, 6, '!', 3);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        x.replace(5, 6, '!', 3);
        x.clear();
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string y("hello world");
        string x(y, 6);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string y("hello world");
        string x(y, 6, 4);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world");
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x("hello world", 5);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x('c');
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    try
    {
        string x('c', 5);
        printf("%s\n", x.v());
    }
    catch(...)
    {

    }

    return 0;
}
