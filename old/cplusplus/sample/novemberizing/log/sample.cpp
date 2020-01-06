/**
 *
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#include <novemberizing/log.hh>

using namespace novemberizing;

int main(int argc, char ** argv)
{
    FUNCTION_START("novemberizing", "function start");
    ERROR_LOG("novemberizing", "error");
    WARNING_LOG("novemberizing", "warning");
    CAUTION_LOG("novemberizing", "caution");
    NOTICE_LOG("novemberizing", "notice");
    INFORMATION_LOG("novemberizing", "information");
    DEBUG_LOG("novemberizing", "debug");
    VERBOSE_LOG("novemberizing", "verbose");
    FUNCTION_END("novemberizing", "function start");

    return 0;
}

