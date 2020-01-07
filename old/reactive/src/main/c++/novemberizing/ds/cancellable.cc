#include "cancellable.hh"

namespace novemberizing { namespace ds {

Cancellable::Cancellable(void) : __cancel(false)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Cancellable::~Cancellable(void)
{
    FUNCTION_START("");

    cancel(true);

    FUNCTION_END("");
}

void Cancellable::cancel(bool v)
{
    FUNCTION_START("");

    __cancel = v;

    FUNCTION_END("");
}

bool Cancellable::cancel(void) const
{
    FUNCTION_START("");
    FUNCTION_END("");
    return __cancel;
}

} }
