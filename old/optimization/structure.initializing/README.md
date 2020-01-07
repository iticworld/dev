# INITIALIZE STRUCTURE

크지 않은 구조체는 간단하게 0 을 삽입하면서 초기화를 수행하지만, 그렇지 않은 경우는 ```rep stos %rax, %es:(%rdi)``` memset 처럼 동작한다.

```
gcc -o a.out main.cpp
objdump -d a.out</pre>
```

## SMALL SIZE STRUCTURE (32)

```
struct hello
{
    int i;
    int v:2;
    int c;
    char buffer[8];
};
```

| ADDRESS | BYTES                         | ASSEMBLY                    | COMMENT                    |
| ------- | ----------------------------- | --------------------------- | -------------------------- |
| 66a     | 55                            | push   %rbp                 | main(...)                  |
| 66b     | 48 89 e5                      | mov    %rsp, %rbp           | -                          |
| 66e     | 48 83 ec 30                   | sub    $0x30, %rsp          | DEFINE LOCAL VARIABLE      |
| 672     | 89 7d dc                      | mov    %edi, -0x24(%rbp)    | -                          |
| 675     | 48 89 75 d0                   | mov    %rsi, -0x30(%rbp)    | -                          |
| 679     | 64 48 8b 04 25 28 00 00 00    | mov    %fs:0x28, %rax       | -                          |
| 682     | 48 89 45 f8                   | mov    %rax, -0x8(%rbp)     | -                          |
| 686     | 31 c0                         | xor    %eax, %eax           | -                          |
| 688     | 48 c7 45 e0 00 00 00 00       | movq   $0x0, -0x20(%rbp)    | INITIALIZE STRUCTURE VALUE |
| 690     | 48 c7 45 e8 00 00 00 00       | movq   $0x0, -0x18(%rbp)    | INITIALIZE STRUCTURE VALUE |
| 698     | c7 45 f0 00 00 00 00          | movl   $0x0, -0x10(%rbp)    | INITIALIZE STRUCTURE VALUE |
| 69f     | b8 00 00 00 00                | mov    $0x0, %eax           | -                          |
| 6a4     | 48 8b 55 f8                   | mov    -0x8(%rbp), %rdx     | -                          |
| 6a8     | 64 48 33 14 25 28 00 00 00    | xor    %fs:0x28, %rdx       | -                          |
| 6b1     | 74 05                         | je     6b8                  | -                          |
| 6b3     | e8 88 fe ff ff                | callq  540                  | -                          |
| 6b8     | c9                            | leaveq                      | -                          |
| 6b9     | c3                            | retq                        | -                          |
| 6ba     | 66 0f 1f 44 00 00             | nopw   0x0(%rax, %rax,1)    | -                          |

## MEDIUM STRUCTURE (64)

```
struct hello
{
    int i;
    int v:2;
    int c;
    char buffer[48];
};
```

| ADDRESS | BYTES                         | ASSEMBLY                    | COMMENT                    |
| ------- | ----------------------------- | --------------------------- | -------------------------- |
| 66a     | 55                            | push   %rbp                 | main(...)                  |
| 66b     | 48 89 e5                      | mov    %rsp, %rbp           | -                          |
| 66e     | 48 83 ec 60                   | sub    $0x60, %rsp          | DEFINE VARIABLE            |
| 672     | 89 7d ac                      | mov    %edi, -0x54(%rbp)    | -                          |
| 675     | 48 89 75 a0                   | mov    %rsi, -0x60(%rbp)    | -                          |
| 679     | 64 48 8b 04 25 28 00 00 00    | mov    %fs:0x28, %rax       | -                          |
| 682     | 48 89 45 f8                   | mov    %rax, -0x8(%rbp)     | -                          |
| 686     | 31 c0                         | xor    %eax, %eax           | -                          |
| 688     | 48 c7 45 b0 00 00 00 00       | movq   $0x0, -0x50(%rbp)    | INITIALIZE STRUCTURE       |
| 690     | 48 c7 45 b8 00 00 00 00       | movq   $0x0, -0x48(%rbp)    | INITIALIZE STRUCTURE       |
| 698     | 48 c7 45 c0 00 00 00 00       | movq   $0x0, -0x40(%rbp)    | INITIALIZE STRUCTURE       |
| 6a0     | 48 c7 45 c8 00 00 00 00       | movq   $0x0, -0x38(%rbp)    | INITIALIZE STRUCTURE       |
| 6a8     | 48 c7 45 d0 00 00 00 00       | movq   $0x0, -0x30(%rbp)    | INITIALIZE STRUCTURE       |
| 6b0     | 48 c7 45 d8 00 00 00 00       | movq   $0x0, -0x28(%rbp)    | INITIALIZE STRUCTURE       |
| 6b8     | 48 c7 45 e0 00 00 00 00       | movq   $0x0, -0x20(%rbp)    | INITIALIZE STRUCTURE       |
| 6c0     | c7 45 e8 00 00 00 00          | movl   $0x0, -0x18(%rbp)    | INITIALIZE STRUCTURE       |
| 6c7     | b8 00 00 00 00                | mov    $0x0, %eax           | -                          |
| 6cc     | 48 8b 55 f8                   | mov    -0x8(%rbp), %rdx     | -                          |
| 6d0     | 64 48 33 14 25 28 00 00 00    | xor    %fs:0x28, %rdx       | -                          |
| 6d9     | 74 05                         | je     6e0                  | -                          |
| 6db     | e8 60 fe ff ff                | callq  540                  | -                          |
| 6e0     | c9                            | leaveq                      | -                          |
| 6e1     | c3                            | retq                        | -                          |
| 6e2     | 66 2e 0f 1f 84 00 00 00 00 00 | nopw   %cs:0x0(%rax,%rax,1) | -                          |
| 6ec     | 0f 1f 40 00                   | nopl   0x0(%rax)            | -                          |


## BIG SIZE (1024)

```
struct hello
{
    int i;
    int v:2;
    int c;
    char buffer[1024];
};
```

| ADDRESS | BYTES                         | ASSEMBLY                    | COMMENT                    |
| ------- | ----------------------------- | --------------------------- | -------------------------- |
| 66a     | 55                            | push   %rbp                 | main(...)                  |
| 66b     | 48 89 e5                      | mov    %rsp, %rbp           | -                          |
| 66e     | 48 81 ec 30 04 00 00          | sub    $0x430, %rsp         | DEFINE VARIABLE            |
| 675     | 89 bd dc fb ff ff             | mov    %edi, -0x424(%rbp)   | -                          |
| 67b     | 48 89 b5 d0 fb ff ff          | mov    %rsi, -0x430(%rbp)   | -                          |
| 682     | 64 48 8b 04 25 28 00 00 00    | mov    %fs:0x28, %rax       | -                          |
| 68b     | 48 89 45 f8                   | mov    %rax, -0x8(%rbp)     | -                          |
| 68f     | 31 c0                         | xor    %eax, %eax           | -                          |
| 691     | 48 8d 95 e0 fb ff ff          | lea    -0x420(%rbp), %rdx   | -                          |
| 698     | b8 00 00 00 00                | mov    $0x0, %eax           | -                          |
| 69d     | b9 81 00 00 00                | mov    $0x81, %ecx          | -                          |
| 6a2     | 48 89 d7                      | mov    %rdx, %rdi           | -                          |
| 6a5     | f3 48 ab                      | rep stos %rax, %es:(%rdi)   | -                          |
| 6a8     | 48 89 fa                      | mov    %rdi, %rdx           | -                          |
| 6ab     | 89 02                         | mov    %eax, (%rdx)         | -                          |
| 6ad     | 48 83 c2 04                   | add    $0x4, %rdx           | -                          |
| 6b1     | b8 00 00 00 00                | mov    $0x0, %eax           | -                          |
| 6b6     | 48 8b 75 f8                   | mov    -0x8(%rbp), %rsi     | -                          |
| 6ba     | 64 48 33 34 25 28 00 00 00    | xor    %fs:0x28, %rsi       | -                          |
| 6c3     | 74 05                         | je     6ca                  | -                          |
| 6c5     | e8 76 fe ff ff                | callq  540                  | -                          |
| 6ca     | c9                            | leaveq                      | -                          |
| 6cb     | c3                            | retq                        | -                          |
| 6cc     | 0f 1f 40 00                   | nopl   0x0(%rax)            | -                          |
