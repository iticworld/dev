#include <stdio.h>
#include <novemberizing/time.h>

int main()
{
    struct timestamp previous = {};
    struct timestamp result = {};
    if(timestamp_get(&previous) == fail)
    {
        printf("fail to timestamp_get(&previous)\n");
        return fail;
    }
    timestamp_out(&previous);
    if(timestamp_gap(&result, &result) == fail)
    {
        printf("fail to timestamp_gap(&result, &result)\n");
        return fail;
    }
    timestamp_out(&result);

    return 0;
}