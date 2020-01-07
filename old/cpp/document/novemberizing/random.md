# NOVEMBERIZING::RANDOM

| method                           | description           |
| -------------------------------- | --------------------- |
| random::get<T>(): T              | get new random number |
| random::get<T>(limit: uint32): T | get new random number |

```random::get<T>(): T``` 함수는 특정 변수형의 랜덤 숫자를 생성합니다.

```random::get<T>(limit: uint32): T``` 함수는 특정 변수형의 랜덤 숫자를 생성하는데, 함수의 인자로 설정한 숫자를 넘지 않는 랜덤 숫자를 생성합니다. 

```
#include <novemberizing/random.hh>

using namespace novemberizing;

#include <cstdio>

int main(int argc, char ** argv)
{
    for(type::int32 i = 0; i < 8; i++)
    {
        printf("%d\n", random::get<type::int32>());
    }
    for(type::int32 i = 0; i < 8; i++)
    {
        printf("%d\n", random::get<type::int32>(64));
    }
    return 0;
}
```
