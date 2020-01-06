# COMPARE "LENGTH -= 1" VS "LENGTH--"

> [source](https://github.com/iticworld/programming/tree/master/optimization/benchmark.substraction)

## SOURCE

```
#include <cstdlib>
#include <ctime>
#include <cstdio>

int main() {
    srand((unsigned int) time(nullptr));
    int i = rand();

    i -= 1;
    printf("%d\n", i);
    i--;
    printf("%d\n", i);
    return 0;
}
```

## COMPILE

```
wget https://raw.githubusercontent.com/iticworld/programming/master/optimization/benchmark.substraction/main.cpp
g++ -std=c++17 -o a.out main.cpp
objdump a.out
```

## DISASSEMBLE

__main(...)__

| ADDRESS | BYTES                | ASSEMBLY                    | DESCRIPTION                 |
| ------- | -------------------- | --------------------------- | --------------------------- |
| 71a     | 55                   | push   %rbp                 | main(...)                   |
| 71b     | 48 89 e5             | mov    %rsp, %rbp           | -                           |
| 71e     | 48 83 ec 10          | sub    $0x10, %rsp          | DEFINE VARIABLE             |
| 722     | bf 00 00 00 00       | mov    $0x0, %edi           | SET EDI = 0                 |
| 727     | e8 b4 fe ff ff       | callq  5e0                  | time(edi)                   |
| 72c     | 89 c7                | mov    %eax, %edi           | SET EDI = RETURN VALUE      |
| 72e     | e8 9d fe ff ff       | callq  5d0                  | srand(edi)                  |
| 733     | e8 b8 fe ff ff       | callq  5f0                  | rand()                      |
| 738     | 89 45 fc             | mov    %eax, -0x4(%rbp)     | SET VARIABLE = RETURN VALUE |
| 73b     | 83 6d fc 01          | subl   $0x1, -0x4(%rbp)     | "i-=1" SUBTRACTION          |
| 73f     | 8b 45 fc             | mov    -0x4(%rbp), %eax     | -                           |
| 742     | 89 c6                | mov    %eax, %esi           | -                           |
| 744     | 48 8d 3d b9 00 00 00 | lea    0xb9(%rip), %rdi     | -                           |
| 74b     | b8 00 00 00 00       | mov    $0x0, %eax           | CLEAR EAX                   |
| 750     | e8 6b fe ff ff       | callq  5c0                  | printf(...)                 |
| 755     | 83 6d fc 01          | subl   $0x1, -0x4(%rbp)     | "i--" SUBTRACTION           |
| 759     | 8b 45 fc             | mov    -0x4(%rbp), %eax     | -                           |
| 75c     | 89 c6                | mov    %eax, %esi           | -                           |
| 75e     | 48 8d 3d 9f 00 00 00 | lea    0x9f(%rip), %rdi     | -                           |
| 765     | b8 00 00 00 00       | mov    $0x0, %eax           | -                           |
| 76a     | e8 51 fe ff ff       | callq  5c0                  | printf(...)                 |
| 76f     | b8 00 00 00 00       | mov    $0x0, %eax           | RETURN 0                    |
| 774     | c9                   | leaveq                      | -                           |
| 775     | c3                   | retq                        | -                           |
| 776     | 66 2e 0f 1f 84 00 00 | nopw   %cs:0x0(%rax,%rax,1) | -                           |
| 77d     | 00 00 00             | -                           | -                           |

## CONCLUSION

두 문장은 틀리지만, 컴파일된 모습은 같다. 사실은 크게 의미가 없어 보인다.
