/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 4.
 */

#include "v1.hh"

namespace novemberizing
{
    namespace secure
    {
        namespace hash
        {
            namespace algorithm
            {
                inline uint32 rotate(uint32 x, uint32 n)
                {
                    return (x << n) | (x >> (32 - n));
                }

                bytes v1::from(const bytes & v)
                {
                    uint32 initial[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
                    uint64 original = v.size(); /** to append 1 (bit) */
                    uint64 remain = (original + 1) % 64;
                    uint64 total = (remain <= 56 ? 1 : 2) + original/64;
                    endian::type endian = endian::get();
                    bytes buffer;
                    uint32 weight[80];
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
                                uint64 len = (endian!=endian::little ? original * 8 : endian::convert(original * 8));
                                buffer = move(bytes::sub(v, i * 64, 64));
                                buffer.append(0x80);
                                buffer.append((byte) 0x00, 56 - buffer.size());
                                buffer.append((byte *) &len, 8);
                            }
                            else
                            {
                                uint64 len = (endian!=endian::little ? original * 8 : endian::convert(original * 8));
                                buffer.assign((byte) 0x00, 56);
                                buffer.append((byte *) &len, 8);
                            }
                        }

                        if(buffer.size() != 64) /** remove this: when release */
                        {
                            throw exception();
                        }
                        for(uint32 j = 0; j < 16; j++)
                        {
                            weight[j] = bytes::to::uinteger32(buffer, sizeof(uint32) * j, endian==endian::little);
                        }
                        for(uint32 j = 16; j < 80; j++)
                        {
                            weight[j] = rotate((weight[j - 3] ^ weight[j - 8] ^ weight[j - 14] ^ weight[j - 16]), 1);
                        }
                        uint32 value[5];

                        value[0] = initial[0];
                        value[1] = initial[1];
                        value[2] = initial[2];
                        value[3] = initial[3];
                        value[4] = initial[4];
                        uint32 f = 0;
                        uint32 k = 0;
                        for(uint32 j = 0; j<20;j++)
                        {
                            f = (value[1] & value[2]) | ((~value[1]) & value[3]);
                            k = 0x5A827999;
                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
                            value[4] = value[3];
                            value[3] = value[2];
                            value[2] = rotate(value[1], 30);
                            value[1] = value[0];
                            value[0] = f;
                        }
                        for(uint32 j = 20; j < 40; j++)
                        {
                            f = (value[1] ^ value[2] ^ value[3]);
                            k = 0x6ED9EBA1;
                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
                            value[4] = value[3];
                            value[3] = value[2];
                            value[2] = rotate(value[1], 30);
                            value[1] = value[0];
                            value[0] = f;
                        }
                        for(uint32 j = 40; j < 60; j++)
                        {
                            f = ((value[1] & value[2]) | (value[1] & value[3]) | (value[2] & value[3]));
                            k = 0x8F1BBCDC;
                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
                            value[4] = value[3];
                            value[3] = value[2];
                            value[2] = rotate(value[1], 30);
                            value[1] = value[0];
                            value[0] = f;
                        }
                        for(uint32 j = 60; j < 80; j++)
                        {
                            f = (value[1] ^ value[2] ^ value[3]);
                            k = 0xCA62C1D6;
                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
                            value[4] = value[3];
                            value[3] = value[2];
                            value[2] = rotate(value[1], 30);
                            value[1] = value[0];
                            value[0] = f;
                        }
                        initial[0] += value[0];
                        initial[1] += value[1];
                        initial[2] += value[2];
                        initial[3] += value[3];
                        initial[4] += value[4];
                    }
                    bytes out;
                    initial[0] = (endian!=endian::little ? initial[0] : endian::convert(initial[0]));
                    initial[1] = (endian!=endian::little ? initial[1] : endian::convert(initial[1]));
                    initial[2] = (endian!=endian::little ? initial[2] : endian::convert(initial[2]));
                    initial[3] = (endian!=endian::little ? initial[3] : endian::convert(initial[3]));
                    initial[4] = (endian!=endian::little ? initial[4] : endian::convert(initial[4]));
                    out.append((byte *) &initial[0], sizeof(uint32));
                    out.append((byte *) &initial[1], sizeof(uint32));
                    out.append((byte *) &initial[2], sizeof(uint32));
                    out.append((byte *) &initial[3], sizeof(uint32));
                    out.append((byte *) &initial[4], sizeof(uint32));
                    return out;
                }

                /**
                 * all variables are unsigned 32 bit quantities and wrap module 1 << 32 when calculating, except for
                 *  ml, the message length, which is a 64 bit quantity, and
                 *  hh, the message digest, which is a 160 bit quantity.
                 *
                 * all constants in this pseudo code are in big endian.
                 * Within each word, the most significant byte is stored in the leftmost byte position.
                 */
//                bytes v1::from(const string & v)
//                {
//                    uint32 initial[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
//                    uint64 original = v.size(); /** to append 1 (bit) */
//                    uint64 remain = (original + 1) % 64;
//                    uint64 total = (remain <= 56 ? 1 : 2) + original/64;
////                printf("original: %lu\n", original);
////                printf("remain: %lu\n", remain);
////                printf("total: %lu\n", total);
//                    endian::type endian = endian::get();
//                    bytes buffer;
//                    uint32 weight[80];
//                    for(uint64 i = 0;i<total;i++)
//                    {
//                        if(i + 2 == total)
//                        {
//                            buffer = move(bytes::from(v, i * 64, 64));
//                            if(remain > 56)
//                            {
//                                buffer.append(0x80);
//                                buffer.append((byte) 0x00, 64 - buffer.size());
//                            }
//                        }
//                        else if(i + 1 == total)
//                        {
//                            if(remain <= 56)
//                            {
//                                uint64 len = (endian!=endian::little ? original * 8 : endian::convert(original * 8));
//                                buffer = move(bytes::from(v, i * 64, 64));
//                                buffer.append(0x80);
//                                buffer.append((byte) 0x00, 56 - buffer.size());
//                                buffer.append((byte *) &len, 8);
//                            }
//                            else
//                            {
//                                uint64 len = (endian!=endian::little ? original * 8 : endian::convert(original * 8));
//                                buffer.assign((byte) 0x00, 56);
//                                buffer.append((byte *) &len, 8);
//                            }
//                        }
//
//                        if(buffer.size() != 64) /** remove this: when release */
//                        {
//                            throw exception();
//                        }
//                        for(uint32 j = 0; j < 16; j++)
//                        {
//                            weight[j] = bytes::to::uinteger32(buffer, sizeof(uint32) * j, endian==endian::little);
//                        }
//                        for(uint32 j = 16; j < 80; j++)
//                        {
//                            weight[j] = rotate((weight[j - 3] ^ weight[j - 8] ^ weight[j - 14] ^ weight[j - 16]), 1);
//                        }
//                        uint32 value[5];
//
//                        value[0] = initial[0];
//                        value[1] = initial[1];
//                        value[2] = initial[2];
//                        value[3] = initial[3];
//                        value[4] = initial[4];
//                        uint32 f = 0;
//                        uint32 k = 0;
//                        for(uint32 j = 0; j<20;j++)
//                        {
//                            f = (value[1] & value[2]) | ((~value[1]) & value[3]);
//                            k = 0x5A827999;
//                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
//                            value[4] = value[3];
//                            value[3] = value[2];
//                            value[2] = rotate(value[1], 30);
//                            value[1] = value[0];
//                            value[0] = f;
//                        }
//                        for(uint32 j = 20; j < 40; j++)
//                        {
//                            f = (value[1] ^ value[2] ^ value[3]);
//                            k = 0x6ED9EBA1;
//                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
//                            value[4] = value[3];
//                            value[3] = value[2];
//                            value[2] = rotate(value[1], 30);
//                            value[1] = value[0];
//                            value[0] = f;
//                        }
//                        for(uint32 j = 40; j < 60; j++)
//                        {
//                            f = ((value[1] & value[2]) | (value[1] & value[3]) | (value[2] & value[3]));
//                            k = 0x8F1BBCDC;
//                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
//                            value[4] = value[3];
//                            value[3] = value[2];
//                            value[2] = rotate(value[1], 30);
//                            value[1] = value[0];
//                            value[0] = f;
//                        }
//                        for(uint32 j = 60; j < 80; j++)
//                        {
//                            f = (value[1] ^ value[2] ^ value[3]);
//                            k = 0xCA62C1D6;
//                            f = rotate(value[0], 5) + f + value[4] + k + weight[j];
//                            value[4] = value[3];
//                            value[3] = value[2];
//                            value[2] = rotate(value[1], 30);
//                            value[1] = value[0];
//                            value[0] = f;
//                        }
//                        initial[0] += value[0];
//                        initial[1] += value[1];
//                        initial[2] += value[2];
//                        initial[3] += value[3];
//                        initial[4] += value[4];
//                    }
//                    bytes out;
//                    initial[0] = (endian!=endian::little ? initial[0] : endian::convert(initial[0]));
//                    initial[1] = (endian!=endian::little ? initial[1] : endian::convert(initial[1]));
//                    initial[2] = (endian!=endian::little ? initial[2] : endian::convert(initial[2]));
//                    initial[3] = (endian!=endian::little ? initial[3] : endian::convert(initial[3]));
//                    initial[4] = (endian!=endian::little ? initial[4] : endian::convert(initial[4]));
//                    out.append((byte *) &initial[0], sizeof(uint32));
//                    out.append((byte *) &initial[1], sizeof(uint32));
//                    out.append((byte *) &initial[2], sizeof(uint32));
//                    out.append((byte *) &initial[3], sizeof(uint32));
//                    out.append((byte *) &initial[4], sizeof(uint32));
//                    return out;
//                }
            }
        }
    }
}

