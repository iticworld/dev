#include <novemberizing.h>

int main(int argc, char ** argv)
{
    FUNCTION_LOG("function");
    ERROR_LOG("error");
    WARNING_LOG("warning");
    CAUTION_LOG("caution");
    NOTICE_LOG("notice");
    INFORMATION_LOG("information");
    DEBUG_LOG("debug");
    VERBOSE_LOG("verbose");
    return 0;
}
