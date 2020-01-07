# EXAMPLE RANDOM USING NOVEMBERIZING C LIB

0. PREREQUISITES

 - install novemberizing c lib [novemberizing c lib](https://github.com/novemberizing/c)
 
1. GET RANDOM INTEGER

```
    random_init();
    for(int i = 0; i<64;i++)
    {
        printf("random number: %d\n", random_get(100));
    }
```
