#include "scheduler.hh"
#include "schedulers/main.hh"

namespace novemberizing { namespace rx {

Scheduler * Scheduler::Main(void) { return schedulers::Main::Get(); }

Scheduler * Scheduler::Self(void) { return schedulers::Main::Get(); }

Scheduler * Scheduler::Local(void) { return schedulers::Main::Get(); }

Scheduler * Scheduler::Get(void) { return schedulers::Main::Get(); }

Scheduler::Scheduler(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

Scheduler::~Scheduler(void)
{
    FUNCTION_START("");
    FUNCTION_END("");
}

} }
