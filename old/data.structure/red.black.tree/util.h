/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 22.
 */

#ifndef   __UTIL__H__
#define   __UTIL__H__

typedef __INT64_TYPE__      integer64;

#define success             (0)
#define fail                (-1)

#define assertion(condition, format, ...)   \
do {                                        \
    if(condition){                          \
        printf(format, ##__VA_ARGS__);      \
        exit(0);                            \
    }                                       \
} while(0)

struct timestamp
{
    integer64 second;
    integer64 nanosecond;
};

extern void random_init();
extern int random_get(int bound);

extern int timestamp_get(struct timestamp * p);
extern void timestamp_out(struct timestamp * p);
extern int timestamp_gap(struct timestamp * p, struct timestamp * previous);

#endif // __UTIL__H__
