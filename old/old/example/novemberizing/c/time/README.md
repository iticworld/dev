# EXAMPLE NOVEMBERIZING C LIB TIME

0. PREREQUISITES

 - install novemberizing c lib. [novemberizing c lib](https://github.com/novemberizing/c)



1. GET CURRENT TIMESTAMP

```
struct timestamp current = {};
if(timestamp_get(&current) == success)
{
    timestamp_out(&current);
}
```

2. CALCULATE TIMESTAMP'S GAP

```
struct timestamp previous = {};
struct timestamp result = {};
if(timestamp_get(&previous) == success)
{
    timestamp_out(&previous);
    if(timestamp_gap(&result, &previous) == success)
    {
        timestamp_out(&result);
    }
}
```