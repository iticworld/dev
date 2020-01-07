# EXAMPLE CODE TO GET DURATION USING NOVEMBERIZING.LIB

간단하게 이전에 기록한 나노초 단위 시간과 현재 시간의 차이를 타임스탬프 객체로 출력해주는 함수에 대한 예제이다.

```
#include <novemberizing.hh>
#include <novemberizing/random.hh>

using namespace novemberizing;

static void print(const timestamp & o)
{
    printf("%ld.%09ld\n", o.second(), o.nanosecond());
}

int main()
{
    timestamp previous = timestamp::get();

    system::sleep(random::get<int64>(65536));

    timestamp v = timestamp::gap(previous);

    print(v);

    return 0;
}
```

이전에 기록한 previous 객체를 파라미터로 입력하면 현재 시간과의 차이를 반환해준다.

```
timestamp v = timestamp::gap(previous)
```
