# COMPARE INLINE VS NORMAL METHOD PERFORMANCE

## EXAMPLE

```
#include <stdio.h>
#include <time.h>

class example
{
public:     inline void hello(){ printf("hello\n"); }
public:     void world();
};

int main()
{
    struct timespec start;
    struct timespec end;
    struct timespec result;
    example x;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < 65536; i++)
    {
        x.hello();
    }
    clock_gettime(CLOCK_REALTIME, &end);
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(result.tv_nsec < 0)
    {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000;
    }
    printf("%ld.%ld\n", result.tv_sec, result.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < 65536; i++)
    {
        x.world();
    }
    clock_gettime(CLOCK_REALTIME, &end);
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(result.tv_nsec < 0)
    {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000;
    }
    printf("%ld.%ld\n", result.tv_sec, result.tv_nsec);

    return 0;
}

void example::world()
{
    printf("world\n");
}
```

## RESULT

| METHOD       | INLINE      | NORMAL      | DIFFERENCE  |
| ------------ | ----------- | ----------- | ----------- |
| SECOND/TOTAL | 0.119482662 | 0.143690239 | 0.024207577 |


## ASSEMBLY

### MAIN

| ADDRESS | BYTES                | ASSEMLBY                    | COMMENTS          |
| ------- | -------------------- | --------------------------- | ----------------- |
| 76a     | 55                   | push   %rbp                 | -                 |
| 76b     | 48 89 e5             | mov    %rsp, %rbp           | -                 |
| 76e     | 48 83 ec 50          | sub    $0x50, %rsp          | -                 |
| 772     | 64 48 8b 04 25 28 00 | mov    %fs:0x28, %rax       | -                 |
| 779     | 00 00                | -                           | -                 |
| 77b     | 48 89 45 f8          | mov    %rax, -0x8(%rbp)     | -                 |
| 77f     | 31 c0                | xor    %eax, %eax           | -                 |
| 781     | 48 8d 45 c0          | lea    -0x40(%rbp), %rax    | -                 |
| 785     | 48 89 c6             | mov    %rax, %rsi           | -                 |
| 788     | bf 00 00 00 00       | mov    $0x0, %edi           | -                 |
| 78d     | e8 8e fe ff ff       | callq  620                  | clock_gettime@plt |
| 792     | c7 45 b8 00 00 00 00 | movl   $0x0, -0x48(%rbp)    | -                 |
| 799     | 81 7d b8 ff ff 00 00 | cmpl   $0xffff, -0x48(%rbp) | -                 |
| 7a0     | 7f 12                | jg     7b4                  | -                 |
| 7a2     | 48 8d 45 b7          | lea    -0x49(%rbp), %rax    | -                 |
| 7a6     | 48 89 c7             | mov    %rax, %rdi           | -                 |
| 7a9     | e8 58 01 00 00       | callq  906                  | example::helloEv  |
| 7ae     | 83 45 b8 01          | addl   $0x1, -0x48(%rbp)    | -                 |
| 7b2     | eb e5                | jmp    799                  | -                 |
| 7b4     | 48 8d 45 d0          | lea    -0x30(%rbp), %rax    | -                 |
| 7b8     | 48 89 c6             | mov    %rax, %rsi           | -                 |
| 7bb     | bf 00 00 00 00       | mov    $0x0, %edi           | -                 |
| 7c0     | e8 5b fe ff ff       | callq  620                  | clock_gettime@plt |
| 7c5     | 48 8b 55 d0          | mov    -0x30(%rbp), %rdx    | -                 |
| 7c9     | 48 8b 45 c0          | mov    -0x40(%rbp), %rax    | -                 |
| 7cd     | 48 29 c2             | sub    %rax, %rdx           | -                 |
| 7d0     | 48 89 d0             | mov    %rdx, %rax           | -                 |
| 7d3     | 48 89 45 e0          | mov    %rax, -0x20(%rbp)    | -                 |
| 7d7     | 48 8b 55 d8          | mov    -0x28(%rbp), %rdx    | -                 |
| 7db     | 48 8b 45 c8          | mov    -0x38(%rbp), %rax    | -                 |
| 7df     | 48 29 c2             | sub    %rax, %rdx           | -                 |
| 7e2     | 48 89 d0             | mov    %rdx, %rax           | -                 |
| 7e5     | 48 89 45 e8          | mov    %rax, -0x18(%rbp)    | -                 |
| 7e9     | 48 8b 45 e8          | mov    -0x18(%rbp), %rax    | -                 |
| 7ed     | 48 85 c0             | test   %rax, %rax           | -                 |
| 7f0     | 79 1a                | jns    80c                  | -                 |
| 7f2     | 48 8b 45 e0          | mov    -0x20(%rbp), %rax    | -                 |
| 7f6     | 48 83 e8 01          | sub    $0x1, %rax           | -                 |
| 7fa     | 48 89 45 e0          | mov    %rax, -0x20(%rbp)    | -                 |
| 7fe     | 48 8b 45 e8          | mov    -0x18(%rbp), %rax    | -                 |
| 802     | 48 05 00 ca 9a 3b    | add    $0x3b9aca00, %rax    | -                 |
| 808     | 48 89 45 e8          | mov    %rax, -0x18(%rbp)    | -                 |
| 80c     | 48 8b 55 e8          | mov    -0x18(%rbp), %rdx    | -                 |
| 810     | 48 8b 45 e0          | mov    -0x20(%rbp), %rax    | -                 |
| 814     | 48 89 c6             | mov    %rax, %rsi           | -                 |
| 817     | 48 8d 3d 9c 01 00 00 | lea    0x19c(%rip), %rdi    | -                 |
| 81e     | b8 00 00 00 00       | mov    $0x0, %eax           | -                 |
| 823     | e8 18 fe ff ff       | callq  640                  | printf@plt        |
| 828     | 48 8d 45 c0          | lea    -0x40(%rbp), %rax    | -                 |
| 82c     | 48 89 c6             | mov    %rax, %rsi           | -                 |
| 82f     | bf 00 00 00 00       | mov    $0x0, %edi           | -                 |
| 834     | e8 e7 fd ff ff       | callq  620                  | clock_gettime@plt |
| 839     | c7 45 bc 00 00 00 00 | movl   $0x0, -0x44(%rbp)    | -                 |
| 840     | 81 7d bc ff ff 00 00 | cmpl   $0xffff, -0x44(%rbp) | -                 |
| 847     | 7f 12                | jg     85b                  | -                 |
| 849     | 48 8d 45 b7          | lea    -0x49(%rbp), %rax    | -                 |
| 84d     | 48 89 c7             | mov    %rax, %rdi           | -                 |
| 850     | e8 95 00 00 00       | callq  8ea                  | example::world    |
| 855     | 83 45 bc 01          | addl   $0x1, -0x44(%rbp)    | -                 |
| 859     | eb e5                | jmp    840                  | -                 |
| 85b     | 48 8d 45 d0          | lea    -0x30(%rbp), %rax    | -                 |
| 85f     | 48 89 c6             | mov    %rax, %rsi           | -                 |
| 862     | bf 00 00 00 00       | mov    $0x0, %edi           | -                 |
| 867     | e8 b4 fd ff ff       | callq  620                  | clock_gettime@plt |
| 86c     | 48 8b 55 d0          | mov    -0x30(%rbp), %rdx    | -                 |
| 870     | 48 8b 45 c0          | mov    -0x40(%rbp), %rax    | -                 |
| 874     | 48 29 c2             | sub    %rax, %rdx           | -                 |
| 877     | 48 89 d0             | mov    %rdx, %rax           | -                 |
| 87a     | 48 89 45 e0          | mov    %rax, -0x20(%rbp)    | -                 |
| 87e     | 48 8b 55 d8          | mov    -0x28(%rbp), %rdx    | -                 |
| 882     | 48 8b 45 c8          | mov    -0x38(%rbp), %rax    | -                 |
| 886     | 48 29 c2             | sub    %rax, %rdx           | -                 |
| 889     | 48 89 d0             | mov    %rdx, %rax           | -                 |
| 88c     | 48 89 45 e8          | mov    %rax, -0x18(%rbp)    | -                 |
| 890     | 48 8b 45 e8          | mov    -0x18(%rbp), %rax    | -                 |
| 894     | 48 85 c0             | test   %rax, %rax           | -                 |
| 897     | 79 1a                | jns    8b3                  | -                 |
| 899     | 48 8b 45 e0          | mov    -0x20(%rbp), %rax    | -                 |
| 89d     | 48 83 e8 01          | sub    $0x1, %rax           | -                 |
| 8a1     | 48 89 45 e0          | mov    %rax, -0x20(%rbp)    | -                 |
| 8a5     | 48 8b 45 e8          | mov    -0x18(%rbp), %rax    | -                 |
| 8a9     | 48 05 00 ca 9a 3b    | add    $0x3b9aca00, %rax    | -                 |
| 8af     | 48 89 45 e8          | mov    %rax, -0x18(%rbp)    | -                 |
| 8b3     | 48 8b 55 e8          | mov    -0x18(%rbp), %rdx    | -                 |
| 8b7     | 48 8b 45 e0          | mov    -0x20(%rbp), %rax    | -                 |
| 8bb     | 48 89 c6             | mov    %rax, %rsi           | -                 |
| 8be     | 48 8d 3d f5 00 00 00 | lea    0xf5(%rip), %rdi     | -                 |
| 8c5     | b8 00 00 00 00       | mov    $0x0, %eax           | -                 |
| 8ca     | e8 71 fd ff ff       | callq  640                  | printf@plt        |
| 8cf     | b8 00 00 00 00       | mov    $0x0, %eax           | -                 |
| 8d4     | 48 8b 4d f8          | mov    -0x8(%rbp), %rcx     | -                 |
| 8d8     | 64 48 33 0c 25 28 00 | xor    %fs:0x28, %rcx       | -                 |
| 8df     | 00 00                | -                           | -                 |
| 8e1     | 74 05                | je     8e8                  | -                 |
| 8e3     | e8 48 fd ff ff       | callq  630                  | -                 |
| 8e8     | c9                   | leaveq                      | -                 |
| 8e9     | c3                   | retq                        | -                 |

00000000000008ea <_ZN7example5worldEv>:

## EXAMPLE::WORLD

| ADDRESS | BYTES                | ASSEMLBY                    | COMMENTS          |
| ------- | -------------------- | --------------------------- | ----------------- |
| 8ea     | 55                   | push   %rbp                 | -                 |
| 8eb     | 48 89 e5             | mov    %rsp, %rbp           | -                 |
| 8ee     | 48 83 ec 10          | sub    $0x10, %rsp          | -                 |
| 8f2     | 48 89 7d f8          | mov    %rdi, -0x8(%rbp)     | -                 |
| 8f6     | 48 8d 3d c8 00 00 00 | lea    0xc8(%rip), %rdi     | -                 |
| 8fd     | e8 0e fd ff ff       | callq  610                  | puts@plt          |
| 902     | 90                   | nop                         | -                 |
| 903     | c9                   | leaveq                      | -                 |
| 904     | c3                   | retq                        | -                 |
| 905     | 90                   | nop                         | -                 |

## EXAMPLE::HELLO

| ADDRESS | BYTES                | ASSEMLBY                    | COMMENTS          |
| ------- | -------------------- | --------------------------- | ----------------- |
| 906     | 55                   | push   %rbp                 | -                 |
| 907     | 48 89 e5             | mov    %rsp, %rbp           | -                 |
| 90a     | 48 83 ec 10          | sub    $0x10, %rsp          | -                 |
| 90e     | 48 89 7d f8          | mov    %rdi, -0x8(%rbp)     | -                 |
| 912     | 48 8d 3d 9b 00 00 00 | lea    0x9b(%rip), %rdi     | -                 |
| 919     | e8 f2 fc ff ff       | callq  610                  | puts@plt          |
| 91e     | 90                   | nop                         | -                 |
| 91f     | c9                   | leaveq                      | -                 |
| 920     | c3                   | retq                        | -                 |
| 921     | 66 2e 0f 1f 84 00 00 | nopw   %cs:0x0(%rax,%rax,1) | -                 |
| 928     | 00 00 00             | -                           | -                 |
| 92b     | 0f 1f 44 00 00       | nopl   0x0(%rax,%rax,1)     | -                 |

## CONCLUSION

최적화 옵션을 주지 않아서, 인라인 메서드의 최적화가 이뤄지지 않았다. 이상하게도 두 함수가 같은데, 항상 인라인 선언을 한 함수가 조금 빠르다. 이 부분에 대한 설명이 필요해 보인다.
실험에서 뭔가 잘못되었는데, 최적화 옵션을 주어서, 인라인 메서드가 함수로 컴파일되어 지는 것이 아니라 코드 속에 삽입될 수 있도록 하여 다시 실험할 것이다.


## RESULT (-O2)

| METHOD       | INLINE      | NORMAL      | DIFFERENCE  |
| ------------ | ----------- | ----------- | ----------- |
| SECOND/TOTAL | 0.136216757 | 0.155258570 | 0.019041813 |

| ADDRESS | BYTES                | ASSEMLBY                    | COMMENTS          |
| ------- | -------------------- | --------------------------- | ----------------- |
| 680     | 41 55                | push   %r13                 | -                 |
| 682     | 41 54                | push   %r12                 | -                 |
| 684     | 31 ff                | xor    %edi, %edi           | -                 |
| 686     | 55                   | push   %rbp                 | -                 |
| 687     | 53                   | push   %rbx                 | -                 |
| 688     | 48 8d 2d a5 02 00 00 | lea    0x2a5(%rip), %rbp    | -                 |
| 68f     | bb 00 00 01 00       | mov    $0x10000, %ebx       | -                 |
| 694     | 48 83 ec 38          | sub    $0x38, %rsp          | -                 |
| 698     | 49 89 e5             | mov    %rsp, %r13           | -                 |
| 69b     | 4c 89 ee             | mov    %r13, %rsi           | -                 |
| 69e     | 64 48 8b 04 25 28 00 | mov    %fs:0x28, %rax       | -                 |
| 6a5     | 00 00                | -                           | -                 |
| 6a7     | 48 89 44 24 28       | mov    %rax, 0x28(%rsp)     | -                 |
| 6ac     | 31 c0                | xor    %eax, %eax           | -                 |
| 6ae     | e8 8d ff ff ff       | callq  640                  | clock_gettime@plt |
| 6b3     | 0f 1f 44 00 00       | nopl   0x0(%rax,%rax,1)     | -                 |
| 6b8     | 48 89 ef             | mov    %rbp, %rdi           | -                 |
| 6bb     | e8 70 ff ff ff       | callq  630                  | puts@plt          |
| 6c0     | 83 eb 01             | sub    $0x1, %ebx           | -                 |
| 6c3     | 75 f3                | jne    6b8                  | -                 |
| 6c5     | 4c 8d 64 24 10       | lea    0x10(%rsp), %r12     | -                 |
| 6ca     | 31 ff                | xor    %edi, %edi           | -                 |
| 6cc     | 4c 89 e6             | mov    %r12, %rsi           | -                 |
| 6cf     | e8 6c ff ff ff       | callq  640                  | clock_gettime@plt |
| 6d4     | 48 8b 54 24 10       | mov    0x10(%rsp), %rdx     | -                 |
| 6d9     | 48 8b 4c 24 18       | mov    0x18(%rsp), %rcx     | -                 |
| 6de     | 48 2b 14 24          | sub    (%rsp), %rdx         | -                 |
| 6e2     | 48 2b 4c 24 08       | sub    0x8(%rsp), %rcx      | -                 |
| 6e7     | 79 0b                | jns    6f4                  | -                 |
| 6e9     | 48 83 ea 01          | sub    $0x1, %rdx           | -                 |
| 6ed     | 48 81 c1 00 ca 9a 3b | add    $0x3b9aca00, %rcx    | -                 |
| 6f4     | 48 8d 35 3f 02 00 00 | lea    0x23f(%rip), %rsi    | -                 |
| 6fb     | bf 01 00 00 00       | mov    $0x1, %edi           | -                 |
| 700     | 31 c0                | xor    %eax, %eax           | -                 |
| 702     | 48 8d 2d 3c 02 00 00 | lea    0x23c(%rip), %rbp    | -                 |
| 709     | bb 00 00 01 00       | mov    $0x10000, %ebx       | -                 |
| 70e     | e8 4d ff ff ff       | callq  660                  | -                 |
| 713     | 4c 89 ee             | mov    %r13, %rsi           | -                 |
| 716     | 31 ff                | xor    %edi, %edi           | -                 |
| 718     | e8 23 ff ff ff       | callq  640                  | clock_gettime@plt |
| 71d     | 0f 1f 00             | nopl   (%rax)               | -                 |
| 720     | 48 89 ef             | mov    %rbp, %rdi           | -                 |
| 723     | e8 08 ff ff ff       | callq  630                  | puts@plt          |
| 728     | 83 eb 01             | sub    $0x1, %ebx           | -                 |
| 72b     | 75 f3                | jne    720                  | -                 |
| 72d     | 31 ff                | xor    %edi, %edi           | -                 |
| 72f     | 4c 89 e6             | mov    %r12, %rsi           | -                 |
| 732     | e8 09 ff ff ff       | callq  640                  | clock_gettime@plt |
| 737     | 48 8b 54 24 10       | mov    0x10(%rsp), %rdx     | -                 |
| 73c     | 48 8b 4c 24 18       | mov    0x18(%rsp), %rcx     | -                 |
| 741     | 48 2b 14 24          | sub    (%rsp), %rdx         | -                 |
| 745     | 48 2b 4c 24 08       | sub    0x8(%rsp), %rcx      | -                 |
| 74a     | 79 0b                | jns    757                  | -                 |
| 74c     | 48 83 ea 01          | sub    $0x1, %rdx           | -                 |
| 750     | 48 81 c1 00 ca 9a 3b | add    $0x3b9aca00, %rcx    | -                 |
| 757     | 48 8d 35 dc 01 00 00 | lea    0x1dc(%rip), %rsi    | -                 |
| 75e     | 31 c0                | xor    %eax, %eax           | -                 |
| 760     | bf 01 00 00 00       | mov    $0x1, %edi           | -                 |
| 765     | e8 f6 fe ff ff       | callq  660                  | -                 |
| 76a     | 31 c0                | xor    %eax, %eax           | -                 |
| 76c     | 48 8b 74 24 28       | mov    0x28(%rsp), %rsi     | -                 |
| 771     | 64 48 33 34 25 28 00 | xor    %fs:0x28, %rsi       | -                 |
| 778     | 00 00                | -                           | -                 |
| 77a     | 75 0b                | jne    787                  | -                 |
| 77c     | 48 83 c4 38          | add    $0x38, %rsp          | -                 |
| 780     | 5b                   | pop    %rbx                 | -                 |
| 781     | 5d                   | pop    %rbp                 | -                 |
| 782     | 41 5c                | pop    %r12                 | -                 |
| 784     | 41 5d                | pop    %r13                 | -                 |
| 786     | c3                   | retq                        | -                 |
| 787     | e8 c4 fe ff ff       | callq  650                  | -                 |
| 78c     | 0f 1f 40 00          | nopl   0x0(%rax)            | -                 |

결국은 오늘은 실패다. -O2를 주었을 때, 둘다 최적화되어서, 둘다 인라인 메서드 처럼 컴파일되었다. 신기한 것은 둘다 인라인 선언을 한 것이 조금 더 빠르다는 것이다.
하지만, 여러 가지 변경해가면서 테스트 해 본 결과 같은 결과가 나왔다. 이 정도의 시간 차이는 언제나 날 수 있는 것이다.

```
#include <stdio.h>
#include <time.h>

class example
{
private:    struct timespec spec;
public:     inline void hello() {
                if(clock_gettime(CLOCK_REALTIME, &spec)!=0)
                {
                    spec.tv_sec = 0;
                    spec.tv_nsec = 1;
                }
            }
public:     virtual void world();
};

int main()
{
    struct timespec start;
    struct timespec end;
    struct timespec result;
    example x;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < 65536; i++)
    {
        x.world();

    }
    clock_gettime(CLOCK_REALTIME, &end);
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(result.tv_nsec < 0)
    {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000;
    }
    printf("%ld.%09ld\n", result.tv_sec, result.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < 65536; i++)
    {
        x.hello();
    }
    clock_gettime(CLOCK_REALTIME, &end);
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(result.tv_nsec < 0)
    {
        result.tv_sec -= 1;
        result.tv_nsec += 1000000000;
    }
    printf("%ld.%09ld\n", result.tv_sec, result.tv_nsec);

    return 0;
}

void  __attribute__ ((noinline)) example::world()
{
    if(clock_gettime(CLOCK_REALTIME, &spec)!=0)
    {
        spec.tv_sec = 0;
        spec.tv_nsec = 1;
    }
}
```

강제적으로 인라인이 적용되지 않도록 하였다.

## RESULT

| ITERATION  | 1           | 2           | 3           | 4           | 5           | 6           | 7           | 8           |
| ---------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| NORMAL     | 0.001734918 | 0.001774110 | 0.001704379 | 0.001716690 | 0.001708552 | 0.001722468 | 0.001728348 | 0.001728459 |
| INLINE     | 0.001655739 | 0.001633439 | 0.001636534 | 0.001632246 | 0.001651529 | 0.001644069 | 0.001655804 | 0.001633610 |
| DIFFERENCE | 0.000079179 | 0.000140671 | 0.000067845 | 0.000084444 | 0.000057023 | 0.000078399 | 0.000072544 | 0.000094849 |

## MAIN

| ADDRESS | BYTES                | ASSEMLBY                    | COMMENTS          |
| ------- | -------------------- | --------------------------- | ----------------- |
| 710     | 41 55                | push   %r13                 | -                 |
| 712     | 41 54                | push   %r12                 | -                 |
| 714     | 31 ff                | xor    %edi, %edi           | -                 |
| 716     | 55                   | push   %rbp                 | -                 |
| 717     | 53                   | push   %rbx                 | -                 |
| 718     | bb 00 00 01 00       | mov    $0x10000, %ebx       | -                 |
| 71d     | 48 83 ec 48          | sub    $0x48, %rsp          | -                 |
| 721     | 64 48 8b 04 25 28 00 | mov    %fs:0x28, %rax       | -                 |
| 728     | 00 00                | -                           | -                 |
| 72a     | 48 89 44 24 38       | mov    %rax, 0x38(%rsp)     | -                 |
| 72f     | 31 c0                | xor    %eax, %eax           | -                 |
| 731     | 49 89 e5             | mov    %rsp, %r13           | -                 |
| 734     | 48 8d 05 55 06 20 00 | lea    0x200655(%rip), %rax | -                 |
| 73b     | 48 8d 6c 24 20       | lea    0x20(%rsp), %rbp     | -                 |
| 740     | 4c 89 ee             | mov    %r13, %rsi           | -                 |
| 743     | 48 89 44 24 20       | mov    %rax, 0x20(%rsp)     | -                 |
| 748     | e8 93 ff ff ff       | callq  6e0                  | clock_gettime@plt |
| 74d     | 0f 1f 00             | nopl   (%rax)               | -                 |
| 750     | 48 89 ef             | mov    %rbp, %rdi           | -                 |
| 753     | e8 f8 01 00 00       | callq  950                  | example::world()  |
| 758     | 83 eb 01             | sub    $0x1, %ebx           | -                 |
| 75b     | 75 f3                | jne    750                  | -                 |
| 75d     | 4c 8d 64 24 10       | lea    0x10(%rsp), %r12     | -                 |
| 762     | 31 ff                | xor    %edi, %edi           | -                 |
| 764     | 4c 89 e6             | mov    %r12, %rsi           | -                 |
| 767     | e8 74 ff ff ff       | callq  6e0                  | clock_gettime@plt |
| 76c     | 48 8b 54 24 10       | mov    0x10(%rsp), %rdx     | -                 |
| 771     | 48 8b 4c 24 18       | mov    0x18(%rsp), %rcx     | -                 |
| 776     | 48 2b 14 24          | sub    (%rsp), %rdx         | -                 |
| 77a     | 48 2b 4c 24 08       | sub    0x8(%rsp), %rcx      | -                 |
| 77f     | 79 0b                | jns    78c                  | -                 |
| 781     | 48 83 ea 01          | sub    $0x1, %rdx           | -                 |
| 785     | 48 81 c1 00 ca 9a 3b | add    $0x3b9aca00, %rcx    | -                 |
| 78c     | 48 8d 35 71 02 00 00 | lea    0x271(%rip), %rsi    | -                 |
| 793     | bf 01 00 00 00       | mov    $0x1, %edi           | -                 |
| 798     | 31 c0                | xor    %eax, %eax           | -                 |
| 79a     | bb 00 00 01 00       | mov    $0x10000, %ebx       | -                 |
| 79f     | 48 83 c5 08          | add    $0x8, %rbp           | -                 |
| 7a3     | e8 28 ff ff ff       | callq  6d0                  | __printf_chk@plt  |
| 7a8     | 4c 89 ee             | mov    %r13, %rsi           | -                 |
| 7ab     | 31 ff                | xor    %edi, %edi           | -                 |
| 7ad     | e8 2e ff ff ff       | callq  6e0                  | clock_gettime@plt |
| 7b2     | 66 0f 1f 44 00 00    | nopw   0x0(%rax,%rax,1)     | -                 |
| 7b8     | 31 ff                | xor    %edi, %edi           | -                 |
| 7ba     | 48 89 ee             | mov    %rbp, %rsi           | example::hello    |
| 7bd     | e8 1e ff ff ff       | callq  6e0                  | clock_gettime@plt |
| 7c2     | 85 c0                | test   %eax, %eax           | -                 |
| 7c4     | 74 12                | je     7d8                  | -                 |
| 7c6     | 48 c7 44 24 28 00 00 | movq   $0x0, 0x28(%rsp)     | -                 |
| 7cd     | 00 00                | -                           | -                 |
| 7cf     | 48 c7 44 24 30 01 00 | movq   $0x1, 0x30(%rsp)     | -                 |
| 7d6     | 00 00                | -                           | -                 |
| 7d8     | 83 eb 01             | sub    $0x1, %ebx           | -                 |
| 7db     | 75 db                | jne    7b8                  | -                 |
| 7dd     | 31 ff                | xor    %edi, %edi           | -                 |
| 7df     | 4c 89 e6             | mov    %r12, %rsi           | -                 |
| 7e2     | e8 f9 fe ff ff       | callq  6e0                  | clock_gettime@plt |
| 7e7     | 48 8b 54 24 10       | mov    0x10(%rsp), %rdx     | -                 |
| 7ec     | 48 8b 4c 24 18       | mov    0x18(%rsp), %rcx     | -                 |
| 7f1     | 48 2b 14 24          | sub    (%rsp), %rdx         | -                 |
| 7f5     | 48 2b 4c 24 08       | sub    0x8(%rsp), %rcx      | -                 |
| 7fa     | 79 0b                | jns    807                  | -                 |
| 7fc     | 48 83 ea 01          | sub    $0x1, %rdx           | -                 |
| 800     | 48 81 c1 00 ca 9a 3b | add    $0x3b9aca00, %rcx    | -                 |
| 807     | 48 8d 35 f6 01 00 00 | lea    0x1f6(%rip), %rsi    | -                 |
| 80e     | 31 c0                | xor    %eax, %eax           | -                 |
| 810     | bf 01 00 00 00       | mov    $0x1, %edi           | -                 |
| 815     | e8 b6 fe ff ff       | callq  6d0                  | __printf_chk@plt  |
| 81a     | 31 c0                | xor    %eax, %eax           | -                 |
| 81c     | 48 8b 54 24 38       | mov    0x38(%rsp), %rdx     | -                 |
| 821     | 64 48 33 14 25 28 00 | xor    %fs:0x28, %rdx       | -                 |
| 828     | 00 00                | -                           | -                 |
| 82a     | 75 0b                | jne    837                  | -                 |
| 82c     | 48 83 c4 48          | add    $0x48, %rsp          | -                 |
| 830     | 5b                   | pop    %rbx                 | -                 |
| 831     | 5d                   | pop    %rbp                 | -                 |
| 832     | 41 5c                | pop    %r12                 | -                 |
| 834     | 41 5d                | pop    %r13                 | -                 |
| 836     | c3                   | retq                        | -                 |
| 837     | e8 b4 fe ff ff       | callq  6f0                  | -                 |
| 83c     | 0f 1f 40 00          | nopl   0x0(%rax)            | -                 |

## CONCLUSION

대략적으로 65536번의 함수 호출을 테스트한 결과 약 1 ~ 1.5 나노초의 수행 시간 차이가 있다. 이것은 파라미터가 하나도 없는 경우에 대해서
테스트한 것이다. 이것을 만약에 여러 파라미터가 존재하는 함수로 만들고 이를 테스트 하면 다른 결과가 나올 것이다.
당연히 인라인 함수가 성능이 더 좋을 것이다. 그리고 간단한 함수는 명시적으로 인라인 메서드를 적용하지 않아도 최적화 시에 적절히 인라인으로 변경된다.
그리고 간단한 함수에 대해서 성능 차이는 크게 없는 것으로 보인다.
