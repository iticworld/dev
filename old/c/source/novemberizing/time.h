/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 21.
 */

#ifndef   __NOVEMBERIZING__TIME__H__
#define   __NOVEMBERIZING__TIME__H__

#include <novemberizing.h>

struct timestamp
{
    integer64 second;
    integer64 nanosecond;
};

extern int timestamp_get(struct timestamp * p);
extern void timestamp_out(struct timestamp * p);
extern int timestamp_gap(struct timestamp * p, struct timestamp * previous);

#endif // __NOVEMBERIZING__TIME__H__
