/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 3.
 */

#include "v5.hh"

namespace novemberizing
{
    namespace message
    {
        namespace digest
        {
            const uint32 v5::__shift[64]   = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
                                               5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
                                               4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
                                               6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
            const uint32 v5::__integer[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                                               0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                                               0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                                               0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                                               0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                                               0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                                               0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                                               0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                                               0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                                               0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                                               0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                                               0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                                               0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                                               0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                                               0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                                               0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

            const uint32 v5::__initial[4]  = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

            inline uint32 rotate(uint32 x, uint32 n)
            {
                return (x << n) | (x >> (32 - n));
            }

            bytes v5::from(const bytes & v)
            {
                uint32 initial[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
                uint64 original = v.size(); /** to append 1 (bit) */
                uint64 remain = (original + 1) % 64;
                uint64 total = (remain <= 56 ? 1 : 2) + original/64;
                endian::type endian = endian::get();
                bytes buffer;
                for(uint64 i = 0;i<total;i++)
                {
                    if(i + 2 == total)
                    {
                        buffer = move(bytes::sub(v, i * 64, 64));
                        if(remain > 56)
                        {
                            buffer.append(0x80);
                            buffer.append((byte) 0x00, 64 - buffer.size());
                        }
                    }
                    else if(i + 1 == total)
                    {
                        if(remain <= 56)
                        {
                            uint64 len = original * 8;
                            buffer = move(bytes::sub(v, i * 64, 64));
                            buffer.append(0x80);
                            buffer.append((byte) 0x00, 56 - buffer.size());
                            buffer.append((byte *) &len, 8);
                        }
                        else
                        {
                            uint64 len = original * 8;
                            buffer.assign((byte) 0x00, 56);
                            buffer.append((byte *) &len, 8);
                        }
                    }

                    if(buffer.size() != 64) /** remove this: when release */
                    {
                        throw exception();
                    }
                    uint32 f = 0;
                    uint32 g = 0;
                    uint32 value[4];
                    value[0] = initial[0];
                    value[1] = initial[1];
                    value[2] = initial[2];
                    value[3] = initial[3];
                    for(uint32 j = 0; j < 16; j++)
                    {
                        f = (value[1] & value[2]) | ((~value[1]) & value[3]);
                        g = j;
                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
                        value[0] = value[3];
                        value[3] = value[2];
                        value[2] = value[1];
                        value[1] = value[1] + rotate(f, __shift[j]);
                    }
                    for(uint32 j = 16; j < 32; j++)
                    {
                        f = (value[3] & value[1]) | ((~value[3]) & value[2]);
                        g = ((5 * j + 1) % 16);
                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
                        value[0] = value[3];
                        value[3] = value[2];
                        value[2] = value[1];
                        value[1] = value[1] + rotate(f, __shift[j]);
                    }
                    for(uint32 j = 32; j < 48; j++)
                    {
                        f = (value[1] ^ value[2] ^ value[3]);
                        g = ((3 * j + 5) % 16);
                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
                        value[0] = value[3];
                        value[3] = value[2];
                        value[2] = value[1];
                        value[1] = value[1] + rotate(f, __shift[j]);
                    }
                    for(uint32 j = 48; j < 64; j++)
                    {
                        f = (value[2] ^ (value[1] | (~value[3])));
                        g = ((7 * j) % 16);
                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
                        value[0] = value[3];
                        value[3] = value[2];
                        value[2] = value[1];
                        value[1] = value[1] + rotate(f, __shift[j]);
                    }
                    initial[0] += value[0];
                    initial[1] += value[1];
                    initial[2] += value[2];
                    initial[3] += value[3];
                }
                bytes out;
                out.append((byte *) &initial[0], sizeof(uint32));
                out.append((byte *) &initial[1], sizeof(uint32));
                out.append((byte *) &initial[2], sizeof(uint32));
                out.append((byte *) &initial[3], sizeof(uint32));
                return out;
            }

//            bytes v5::from(const string & v)
//            {
//                uint32 initial[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
//                uint64 original = v.size(); /** to append 1 (bit) */
//                uint64 remain = (original + 1) % 64;
//                uint64 total = (remain <= 56 ? 1 : 2) + original/64;
//                endian::type endian = endian::get();
//                bytes buffer;
//                for(uint64 i = 0;i<total;i++)
//                {
//                    if(i + 2 == total)
//                    {
//                        buffer = move(bytes::from(v, i * 64, 64));
//                        if(remain > 56)
//                        {
//                            buffer.append(0x80);
//                            buffer.append((byte) 0x00, 64 - buffer.size());
//                        }
//                    }
//                    else if(i + 1 == total)
//                    {
//                        if(remain <= 56)
//                        {
//                            uint64 len = original * 8;
//                            buffer = move(bytes::from(v, i * 64, 64));
//                            buffer.append(0x80);
//                            buffer.append((byte) 0x00, 56 - buffer.size());
//                            buffer.append((byte *) &len, 8);
//                        }
//                        else
//                        {
//                            uint64 len = original * 8;
//                            buffer.assign((byte) 0x00, 56);
//                            buffer.append((byte *) &len, 8);
//                        }
//                    }
//
//                    if(buffer.size() != 64) /** remove this: when release */
//                    {
//                        throw exception();
//                    }
//                    uint32 f = 0;
//                    uint32 g = 0;
//                    uint32 value[4];
//                    value[0] = initial[0];
//                    value[1] = initial[1];
//                    value[2] = initial[2];
//                    value[3] = initial[3];
//                    for(uint32 j = 0; j < 16; j++)
//                    {
//                        f = (value[1] & value[2]) | ((~value[1]) & value[3]);
//                        g = j;
//                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
//                        value[0] = value[3];
//                        value[3] = value[2];
//                        value[2] = value[1];
//                        value[1] = value[1] + rotate(f, __shift[j]);
//                    }
//                    for(uint32 j = 16; j < 32; j++)
//                    {
//                        f = (value[3] & value[1]) | ((~value[3]) & value[2]);
//                        g = ((5 * j + 1) % 16);
//                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
//                        value[0] = value[3];
//                        value[3] = value[2];
//                        value[2] = value[1];
//                        value[1] = value[1] + rotate(f, __shift[j]);
//                    }
//                    for(uint32 j = 32; j < 48; j++)
//                    {
//                        f = (value[1] ^ value[2] ^ value[3]);
//                        g = ((3 * j + 5) % 16);
//                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
//                        value[0] = value[3];
//                        value[3] = value[2];
//                        value[2] = value[1];
//                        value[1] = value[1] + rotate(f, __shift[j]);
//                    }
//                    for(uint32 j = 48; j < 64; j++)
//                    {
//                        f = (value[2] ^ (value[1] | (~value[3])));
//                        g = ((7 * j) % 16);
//                        f = f + value[0] + __integer[j] + bytes::to::uinteger32(buffer, sizeof(uint32) * g, endian!=endian::little);
//                        value[0] = value[3];
//                        value[3] = value[2];
//                        value[2] = value[1];
//                        value[1] = value[1] + rotate(f, __shift[j]);
//                    }
//                    initial[0] += value[0];
//                    initial[1] += value[1];
//                    initial[2] += value[2];
//                    initial[3] += value[3];
//                }
//                bytes out;
//                out.append((byte *) &initial[0], sizeof(uint32));
//                out.append((byte *) &initial[1], sizeof(uint32));
//                out.append((byte *) &initial[2], sizeof(uint32));
//                out.append((byte *) &initial[3], sizeof(uint32));
//                return out;
//            }
        }
    }
}