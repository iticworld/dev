# BENCHMARK IF VS THROW

__PREREQUISITES__

 - [novemberizing c++](https://github.com/novemberizing/cplusplus)
 
__RESULTS__

| IF          | THROW       |
| ----------- | ----------- |
| 0x000000053 | 0.000002712 |
 
__DISASSEMBLE__

1. EXAMPLE IF METHOD

| ADDRESS | BYTES                | ASSEMBLY                   | DESCRIPTION                              |
| ------- | -------------------- | -------------------------- | ---------------------------------------- |
| 154a    | 55                   | push   %rbp                | -                                        |
| 154b    | 48 89 e5             | mov    %rsp,%rbp           | -                                        |
| 154e    | 53                   | push   %rbx                | -                                        |
| 154f    | 48 81 ec 98 00 00 00 | sub    $0x98,%rsp          | -                                        |
| 1556    | 64 48 8b 04 25 28 00 | mov    %fs:0x28,%rax       | -                                        |
| 155d    | 00 00                | -                          | -                                        |
| 155f    | 48 89 45 e8          | mov    %rax,-0x18(%rbp)    | -                                        |
| 1563    | 31 c0                | xor    %eax,%eax           | -                                        |
| 1565    | 48 8d 3d 28 11 00 00 | lea    0x1128(%rip),%rdi   | -                                        |
| 156c    | e8 5f fe ff ff       | callq  13d0                | puts@plt                                 |
| 1571    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 1578    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 157b    | e8 b2 0e 00 00       | callq  2432                | novemberizing::timestamp::timestamp(...) |
| 1580    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1584    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1587    | e8 a6 0e 00 00       | callq  2432                | novemberizing::timestamp::timestamp(...) |
| 158c    | c7 85 68 ff ff ff 00 | movl   $0x0,-0x98(%rbp)    | -                                        |
| 1593    | 00 00 00             | -                          | -                                        |
| 1596    | 81 bd 68 ff ff ff ff | cmpl   $0x3ff,-0x98(%rbp)  | -                                        |
| 159d    | 03 00 00             | -                          | -                                        |
| 15a0    | 0f 8f ea 00 00 00    | jg     1690                | if                                       |
| 15a6    | bf 00 00 01 00       | mov    $0x10000,%edi       | -                                        |
| 15ab    | e8 92 0b 00 00       | callq  2142                | novemberizing::random::get(...)          |
| 15b0    | 89 85 6c ff ff ff    | mov    %eax,-0x94(%rbp)    | -                                        |
| 15b6    | 48 8d 45 b0          | lea    -0x50(%rbp),%rax    | -                                        |
| 15ba    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 15bd    | e8 9e 07 00 00       | callq  1d60                | novemberizing::timestamp::get()          |
| 15c2    | 48 8d 55 b0          | lea    -0x50(%rbp),%rdx    | -                                        |
| 15c6    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 15cd    | 48 89 d6             | mov    %rdx,%rsi           | -                                        |
| 15d0    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 15d3    | e8 ce 08 00 00       | callq  1ea6                | -                                        |
| 15d8    | 48 8d 45 b0          | lea    -0x50(%rbp),%rax    | -                                        |
| 15dc    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 15df    | e8 64 08 00 00       | callq  1e48                | -                                        |
| 15e4    | 8b 85 6c ff ff ff    | mov    -0x94(%rbp),%eax    | -                                        |
| 15ea    | 83 e0 07             | and    $0x7,%eax           | -                                        |
| 15ed    | 85 c0                | test   %eax,%eax           | -                                        |
| 15ef    | 75 2c                | jne    161d                | -                                        |
| 15f1    | 8b 85 6c ff ff ff    | mov    -0x94(%rbp),%eax    | -                                        |
| 15f7    | 0f b7 c0             | movzwl %ax,%eax            | -                                        |
| 15fa    | 85 c0                | test   %eax,%eax           | -                                        |
| 15fc    | 0f 85 82 00 00 00    | jne    1684                | -                                        |
| 1602    | 8b 85 6c ff ff ff    | mov    -0x94(%rbp),%eax    | -                                        |
| 1608    | 89 c6                | mov    %eax,%esi           | -                                        |
| 160a    | 48 8d 3d 86 10 00 00 | lea    0x1086(%rip),%rdi   | -                                        |
| 1611    | b8 00 00 00 00       | mov    $0x0,%eax           | -                                        |
| 1616    | e8 c5 fc ff ff       | callq  12e0                | printf@plt                               |
| 161b    | eb 67                | jmp    1684                | -                                        |
| 161d    | 48 8d 45 d0          | lea    -0x30(%rbp),%rax    | -                                        |
| 1621    | 48 8d 95 70 ff ff ff | lea    -0x90(%rbp),%rdx    | -                                        |
| 1628    | 48 89 d6             | mov    %rdx,%rsi           | -                                        |
| 162b    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 162e    | e8 4b 07 00 00       | callq  1d7e                | novemberizing::timestamp::gap(...)       |
| 1633    | 48 8d 55 d0          | lea    -0x30(%rbp),%rdx    | -                                        |
| 1637    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 163b    | 48 89 d6             | mov    %rdx,%rsi           | -                                        |
| 163e    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1641    | e8 60 08 00 00       | callq  1ea6                | -                                        |
| 1646    | 48 8d 45 d0          | lea    -0x30(%rbp),%rax    | -                                        |
| 164a    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 164d    | e8 f6 07 00 00       | callq  1e48                | -                                        |
| 1652    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1656    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1659    | e8 bc 08 00 00       | callq  1f1a                | -                                        |
| 165e    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 1661    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1665    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1668    | e8 9b 08 00 00       | callq  1f08                | -                                        |
| 166d    | 48 89 da             | mov    %rbx,%rdx           | -                                        |
| 1670    | 48 89 c6             | mov    %rax,%rsi           | -                                        |
| 1673    | 48 8d 3d 31 10 00 00 | lea    0x1031(%rip),%rdi   | -                                        |
| 167a    | b8 00 00 00 00       | mov    $0x0,%eax           | -                                        |
| 167f    | e8 5c fc ff ff       | callq  12e0                | printf@plt                               |
| 1684    | 83 85 68 ff ff ff 01 | addl   $0x1,-0x98(%rbp)    | -                                        |
| 168b    | e9 06 ff ff ff       | jmpq   1596                | -                                        |
| 1690    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1694    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1697    | e8 ac 07 00 00       | callq  1e48                | -                                        |
| 169c    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 16a3    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 16a6    | e8 9d 07 00 00       | callq  1e48                | -                                        |
| 16ab    | 90                   | nop                        | -                                        |
| 16ac    | 48 8b 45 e8          | mov    -0x18(%rbp),%rax    | -                                        |
| 16b0    | 64 48 33 04 25 28 00 | xor    %fs:0x28,%rax       | -                                        |
| 16b7    | 00 00                | -                          | -                                        |
| 16b9    | 74 35                | je     16f0                | -                                        |
| 16bb    | eb 2e                | jmp    16eb                | -                                        |
| 16bd    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 16c0    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 16c4    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 16c7    | e8 7c 07 00 00       | callq  1e48                | -                                        |
| 16cc    | eb 03                | jmp    16d1                | -                                        |
| 16ce    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 16d1    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 16d8    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 16db    | e8 68 07 00 00       | callq  1e48                | -                                        |
| 16e0    | 48 89 d8             | mov    %rbx,%rax           | -                                        |
| 16e3    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 16e6    | e8 35 fd ff ff       | callq  1420                | -                                        |
| 16eb    | e8 a0 fc ff ff       | callq  1390                | -                                        |
| 16f0    | 48 81 c4 98 00 00 00 | add    $0x98,%rsp          | -                                        |
| 16f7    | 5b                   | pop    %rbx                | -                                        |
| 16f8    | 5d                   | pop    %rbp                | -                                        |
| 16f9    | c3                   | retq                       | -                                        |

2. EXAMPLE THROW METHOD

| ADDRESS | BYTES                | ASSEMBLY                   | DESCRIPTION                              |
| ------- | -------------------- | -------------------------- | ---------------------------------------- |
| 16fa    | 55                   | push   %rbp                | -                                        |
| 16fb    | 48 89 e5             | mov    %rsp,%rbp           | -                                        |
| 16fe    | 53                   | push   %rbx                | -                                        |
| 16ff    | 48 81 ec 98 00 00 00 | sub    $0x98,%rsp          | -                                        |
| 1706    | 64 48 8b 04 25 28 00 | mov    %fs:0x28,%rax       | -                                        |
| 170d    | 00 00                | -                          | -                                        |
| 170f    | 48 89 45 e8          | mov    %rax,-0x18(%rbp)    | -                                        |
| 1713    | 31 c0                | xor    %eax,%eax           | -                                        |
| 1715    | 48 8d 3d 9a 0f 00 00 | lea    0xf9a(%rip),%rdi    | -                                        |
| 171c    | e8 af fc ff ff       | callq  13d0                | puts@plt                                 |
| 1721    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 1728    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 172b    | e8 02 0d 00 00       | callq  2432                | -                                        |
| 1730    | 48 8d 45 90          | lea    -0x70(%rbp), %rax   | -                                        |
| 1734    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1737    | e8 f6 0c 00 00       | callq  2432                | -                                        |
| 173c    | c7 85 64 ff ff ff 00 | movl   $0x0,-0x9c(%rbp)    | -                                        |
| 1743    | 00 00 00             | -                          | -                                        |
| 1746    | 81 bd 64 ff ff ff ff | cmpl   $0x3ff,-0x9c(%rbp)  | -                                        |
| 174d    | 03 00 00             | -                          | -                                        |
| 1750    | 0f 8f a3 00 00 00    | jg     17f9                | -                                        |
| 1756    | bf 00 00 01 00       | mov    $0x10000, %edi      | -                                        |
| 175b    | e8 e2 09 00 00       | callq  2142                | -                                        |
| 1760    | 89 85 68 ff ff ff    | mov    %eax,-0x98(%rbp)    | -                                        |
| 1766    | 48 8d 45 b0          | lea    -0x50(%rbp),%rax    | -                                        |
| 176a    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 176d    | e8 ee 05 00 00       | callq  1d60                | -                                        |
| 1772    | 48 8d 55 b0          | lea    -0x50(%rbp),%rdx    | -                                        |
| 1776    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 177d    | 48 89 d6             | mov    %rdx,%rsi           | -                                        |
| 1780    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1783    | e8 1e 07 00 00       | callq  1ea6                | -                                        |
| 1788    | 48 8d 45 b0          | lea    -0x50(%rbp),%rax    | -                                        |
| 178c    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 178f    | e8 b4 06 00 00       | callq  1e48                | -                                        |
| 1794    | 8b 85 68 ff ff ff    | mov    -0x98(%rbp),%eax    | -                                        |
| 179a    | 83 e0 07             | and    $0x7,%eax           | -                                        |
| 179d    | 85 c0                | test   %eax,%eax           | -                                        |
| 179f    | 74 26                | je     17c7                | -                                        |
| 17a1    | bf 04 00 00 00       | mov    $0x4,%edi           | -                                        |
| 17a6    | e8 65 fb ff ff       | callq  1310                | __cxa_allocate_exception@plt             |
| 17ab    | 8b 95 68 ff ff ff    | mov    -0x98(%rbp),%edx    | -                                        |
| 17b1    | 89 10                | mov    %edx,(%rax)         | -                                        |
| 17b3    | ba 00 00 00 00       | mov    $0x0,%edx           | -                                        |
| 17b8    | 48 8d 35 41 24 20 00 | lea    0x202441(%rip),%rsi | _ZTIi@@CXXABI_1.3                        |
| 17bf    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 17c2    | e8 49 fc ff ff       | callq  1410                | __cxa_throw@plt                          |
| 17c7    | 8b 85 68 ff ff ff    | mov    -0x98(%rbp),%eax    | -                                        |
| 17cd    | 0f b7 c0             | movzwl %ax,%eax            | -                                        |
| 17d0    | 85 c0                | test   %eax,%eax           | -                                        |
| 17d2    | 75 19                | jne    17ed                | -                                        |
| 17d4    | 8b 85 68 ff ff ff    | mov    -0x98(%rbp),%eax    | -                                        |
| 17da    | 89 c6                | mov    %eax,%esi           | -                                        |
| 17dc    | 48 8d 3d b4 0e 00 00 | lea    0xeb4(%rip),%rdi    | -                                        |
| 17e3    | b8 00 00 00 00       | mov    $0x0,%eax           | -                                        |
| 17e8    | e8 f3 fa ff ff       | callq  12e0                | -                                        |
| 17ed    | 83 85 64 ff ff ff 01 | addl   $0x1,-0x9c(%rbp)    | -                                        |
| 17f4    | e9 4d ff ff ff       | jmpq   1746                | -                                        |
| 17f9    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 17fd    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1800    | e8 43 06 00 00       | callq  1e48                | -                                        |
| 1805    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 180c    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 180f    | e8 34 06 00 00       | callq  1e48                | -                                        |
| 1814    | 90                   | nop                        | -                                        |
| 1815    | 48 8b 45 e8          | mov    -0x18(%rbp),%rax    | -                                        |
| 1819    | 64 48 33 04 25 28 00 | xor    %fs:0x28,%rax       | -                                        |
| 1820    | 00 00                | -                          | -                                        |
| 1822    | 0f 84 d1 00 00 00    | je     18f9                | -                                        |
| 1828    | e9 c7 00 00 00       | jmpq   18f4                | -                                        |
| 182d    | 48 83 fa 01          | cmp    $0x1,%rdx           | -                                        |
| 1831    | 74 08                | je     183b                | -                                        |
| 1833    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 1836    | e9 8e 00 00 00       | jmpq   18c9                | -                                        |
| 183b    | 48 89 c7             | mov    %rax, %rdi          | -                                        |
| 183e    | e8 bd fa ff ff       | callq  1300                | __cxa_begin_catch@plt                    |
| 1843    | 8b 00                | mov    (%rax),%eax         | -                                        |
| 1845    | 89 85 6c ff ff ff    | mov    %eax,-0x94(%rbp)    | -                                        |
| 184b    | 48 8d 45 d0          | lea    -0x30(%rbp),%rax    | -                                        |
| 184f    | 48 8d 95 70 ff ff ff | lea    -0x90(%rbp),%rdx    | -                                        |
| 1856    | 48 89 d6             | mov    %rdx, %rsi          | -                                        |
| 1859    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 185c    | e8 1d 05 00 00       | callq  1d7e                | -                                        |
| 1861    | 48 8d 55 d0          | lea    -0x30(%rbp),%rdx    | -                                        |
| 1865    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1869    | 48 89 d6             | mov    %rdx,%rsi           | -                                        |
| 186c    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 186f    | e8 32 06 00 00       | callq  1ea6                | -                                        |
| 1874    | 48 8d 45 d0          | lea    -0x30(%rbp),%rax    | -                                        |
| 1878    | 48 89 c7             | mov    %rax, %rdi          | -                                        |
| 187b    | e8 c8 05 00 00       | callq  1e48                | -                                        |
| 1880    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1884    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1887    | e8 8e 06 00 00       | callq  1f1a                | -                                        |
| 188c    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 188f    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 1893    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 1896    | e8 6d 06 00 00       | callq  1f08                | -                                        |
| 189b    | 48 89 da             | mov    %rbx,%rdx           | -                                        |
| 189e    | 48 89 c6             | mov    %rax,%rsi           | -                                        |
| 18a1    | 48 8d 3d 03 0e 00 00 | lea    0xe03(%rip),%rdi    | -                                        |
| 18a8    | b8 00 00 00 00       | mov    $0x0,%eax           | -                                        |
| 18ad    | e8 2e fa ff ff       | callq  12e0                | -                                        |
| 18b2    | e8 39 fb ff ff       | callq  13f0                | __cxa_end_catch@plt                      |
| 18b7    | e9 31 ff ff ff       | jmpq   17ed                | -                                        |
| 18bc    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 18bf    | e8 2c fb ff ff       | callq  13f0                | __cxa_end_catch@plt                      |
| 18c4    | eb 03                | jmp    18c9                | -                                        |
| 18c6    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 18c9    | 48 8d 45 90          | lea    -0x70(%rbp),%rax    | -                                        |
| 18cd    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 18d0    | e8 73 05 00 00       | callq  1e48                | -                                        |
| 18d5    | eb 03                | jmp    18da                | -                                        |
| 18d7    | 48 89 c3             | mov    %rax,%rbx           | -                                        |
| 18da    | 48 8d 85 70 ff ff ff | lea    -0x90(%rbp),%rax    | -                                        |
| 18e1    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 18e4    | e8 5f 05 00 00       | callq  1e48                | -                                        |
| 18e9    | 48 89 d8             | mov    %rbx,%rax           | -                                        |
| 18ec    | 48 89 c7             | mov    %rax,%rdi           | -                                        |
| 18ef    | e8 2c fb ff ff       | callq  1420                | -                                        |
| 18f4    | e8 97 fa ff ff       | callq  1390                | -                                        |
| 18f9    | 48 81 c4 98 00 00 00 | add    $0x98,%rsp          | -                                        |
| 1900    | 5b                   | pop    %rbx                | -                                        |
| 1901    | 5d                   | pop    %rbp                | -                                        |
| 1902    | c3                   | retq                       | -                                        |

## CONCLUSION

예외 처리 시에 TRY, CATCH BLOCK 은 특정 로직을 __cxa_allocate_exception, __cxa_begin_catch, __cxa_end_catch 함수로 감싸는 로직이 들어간다.
이것이 처리될 때 시간이 소요되는 것으로 보인다. 다만 EXCEPTION 이 발생하지 않도록, 짠다면, 성능 저하를 일으키지 않을 것 같다.
그래서, 일부터 THROW 를 발생시켜서 로직을 처리하기 보다, IF 문으로 처리할 수 있는 것을 IF 처리하도록 하자.
THROW 는 정말 처리되지 않는 로직에 대해서만 THROW 를 발생 시키자.

## TODO

 - __cxa_allocate_exception
 - __cxa_begin_catch
 - __cxa_end_catch