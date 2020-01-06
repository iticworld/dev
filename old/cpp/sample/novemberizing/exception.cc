#include <novemberizing/exception.hh>

using namespace novemberizing;

int main(int argc, char ** argv)
{
    try
    {
        throw exception(); // NOLINT
    }
    catch(const exception & e)
    {

    }
    return 0;
}

