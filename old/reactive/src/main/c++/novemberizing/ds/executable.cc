#include "executable.hh"

namespace novemberizing { namespace ds {

Executable::Executable(void) : __executor(nullptr)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Executable::~Executable(void)
{
    FUNCTION_START("");

    if(__executor!=nullptr)
    {
        Executor * executor = __executor;
        executor->completed(this);
        __executor = nullptr;
    }

    FUNCTION_END("");
}

void Executable::execute(Executor * executor)
{
    FUNCTION_START("");
    if(__executor!=nullptr)
    {
        WARNING_LOG("");
    }
    __executor = executor;
    execute();
    FUNCTION_END("");
}

} }
