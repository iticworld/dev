/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 4.
 */

#include "v2.hh"

namespace novemberizing
{
    namespace secure
    {
        namespace hash
        {
            namespace algorithm
            {
                const uint32 __integer[64] = {
                        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
                };

                inline uint32 rotate(uint32 x, uint32 n)
                {
                    return (x >> n) | (x << (32 - n));
                }

                /**
                 * all variables are 32 bit unsigned integers and addition is calculated module square(2, 32)
                 *
                 * for each round, there is one round constant k[i] and one entry in the message schedule array w[i], 0 <= o <= 63
                 *
                 * the compression function uses 8 working variables, a through h
                 *
                 * big endian convention is used when expressing the constants, and when parsing message block data
                 * from bytes to words, for example the first word of the input message "abc" after padding is
                 * 0x61626380
                 */
//                bytes v2::from(const string & v)
//                {
//                    uint32 initial[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
//                    uint64 original = v.size(); /** to append 1 (bit) */
//                    uint64 remain = (original + 1) % 64;
//                    uint64 total = (remain <= 56 ? 1 : 2) + original/64;
//                    endian::type endian = endian::get();
//                    bytes buffer;
//                    uint32 weight[64];
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
//                        for(uint32 j = 16; j < 64; j++)
//                        {
//                            uint32 x = (rotate(weight[j - 15],  7) ^ rotate(weight[j - 15], 18) ^ (weight[j - 15] >>  3U));
//                            uint32 y = (rotate(weight[j -  2], 17) ^ rotate(weight[j -  2], 19) ^ (weight[j -  2] >> 10U));
//                            weight[j] = weight[j - 16] + x + weight[j - 7] + y;
//                        }
//                        uint32 value[8];
//
//                        value[0] = initial[0];
//                        value[1] = initial[1];
//                        value[2] = initial[2];
//                        value[3] = initial[3];
//                        value[4] = initial[4];
//                        value[5] = initial[5];
//                        value[6] = initial[6];
//                        value[7] = initial[7];
//
//                        for(uint32 j = 0; j<64;j++)
//                        {
//                            uint32 a = (rotate(value[4], 6) ^ rotate(value[4], 11) ^ rotate(value[4], 25));
//                            uint32 b = (value[4] & value[5]) ^ ((~value[4]) & value[6]);
//                            uint32 c = value[7] + a + b + __integer[j] + weight[j];
//                            uint32 x = (rotate(value[0], 2) ^ rotate(value[0], 13) ^ rotate(value[0], 22));
//                            uint32 y = ((value[0] & value[1]) ^ (value[0] & value[2]) ^ (value[1] & value[2]));
//                            uint32 z = x + y;
//
//                            value[7] = value[6];
//                            value[6] = value[5];
//                            value[5] = value[4];
//                            value[4] = value[3] + c;
//                            value[3] = value[2];
//                            value[2] = value[1];
//                            value[1] = value[0];
//                            value[0] = c + z;
//                        }
//                        initial[0] += value[0];
//                        initial[1] += value[1];
//                        initial[2] += value[2];
//                        initial[3] += value[3];
//                        initial[4] += value[4];
//                        initial[5] += value[5];
//                        initial[6] += value[6];
//                        initial[7] += value[7];
//                    }
//                    bytes out;
//                    initial[0] = (endian!=endian::little ? initial[0] : endian::convert(initial[0]));
//                    initial[1] = (endian!=endian::little ? initial[1] : endian::convert(initial[1]));
//                    initial[2] = (endian!=endian::little ? initial[2] : endian::convert(initial[2]));
//                    initial[3] = (endian!=endian::little ? initial[3] : endian::convert(initial[3]));
//                    initial[4] = (endian!=endian::little ? initial[4] : endian::convert(initial[4]));
//                    initial[5] = (endian!=endian::little ? initial[4] : endian::convert(initial[5]));
//                    initial[6] = (endian!=endian::little ? initial[4] : endian::convert(initial[6]));
//                    initial[7] = (endian!=endian::little ? initial[4] : endian::convert(initial[7]));
//                    out.append((byte *) &initial[0], sizeof(uint32));
//                    out.append((byte *) &initial[1], sizeof(uint32));
//                    out.append((byte *) &initial[2], sizeof(uint32));
//                    out.append((byte *) &initial[3], sizeof(uint32));
//                    out.append((byte *) &initial[4], sizeof(uint32));
//                    out.append((byte *) &initial[5], sizeof(uint32));
//                    out.append((byte *) &initial[6], sizeof(uint32));
//                    out.append((byte *) &initial[7], sizeof(uint32));
//                    return out;
//                }

                bytes v2::from(const bytes & v)
                {
                    uint32 initial[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
                    uint64 original = v.size(); /** to append 1 (bit) */
                    uint64 remain = (original + 1) % 64;
                    uint64 total = (remain <= 56 ? 1 : 2) + original/64;
                    endian::type endian = endian::get();
                    bytes buffer;
                    uint32 weight[64];
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
                        for(uint32 j = 16; j < 64; j++)
                        {
                            uint32 x = (rotate(weight[j - 15],  7) ^ rotate(weight[j - 15], 18) ^ (weight[j - 15] >>  3U));
                            uint32 y = (rotate(weight[j -  2], 17) ^ rotate(weight[j -  2], 19) ^ (weight[j -  2] >> 10U));
                            weight[j] = weight[j - 16] + x + weight[j - 7] + y;
                        }
                        uint32 value[8];

                        value[0] = initial[0];
                        value[1] = initial[1];
                        value[2] = initial[2];
                        value[3] = initial[3];
                        value[4] = initial[4];
                        value[5] = initial[5];
                        value[6] = initial[6];
                        value[7] = initial[7];

                        for(uint32 j = 0; j<64;j++)
                        {
                            uint32 a = (rotate(value[4], 6) ^ rotate(value[4], 11) ^ rotate(value[4], 25));
                            uint32 b = (value[4] & value[5]) ^ ((~value[4]) & value[6]);
                            uint32 c = value[7] + a + b + __integer[j] + weight[j];
                            uint32 x = (rotate(value[0], 2) ^ rotate(value[0], 13) ^ rotate(value[0], 22));
                            uint32 y = ((value[0] & value[1]) ^ (value[0] & value[2]) ^ (value[1] & value[2]));
                            uint32 z = x + y;

                            value[7] = value[6];
                            value[6] = value[5];
                            value[5] = value[4];
                            value[4] = value[3] + c;
                            value[3] = value[2];
                            value[2] = value[1];
                            value[1] = value[0];
                            value[0] = c + z;
                        }
                        initial[0] += value[0];
                        initial[1] += value[1];
                        initial[2] += value[2];
                        initial[3] += value[3];
                        initial[4] += value[4];
                        initial[5] += value[5];
                        initial[6] += value[6];
                        initial[7] += value[7];
                    }
                    bytes out;
                    initial[0] = (endian!=endian::little ? initial[0] : endian::convert(initial[0]));
                    initial[1] = (endian!=endian::little ? initial[1] : endian::convert(initial[1]));
                    initial[2] = (endian!=endian::little ? initial[2] : endian::convert(initial[2]));
                    initial[3] = (endian!=endian::little ? initial[3] : endian::convert(initial[3]));
                    initial[4] = (endian!=endian::little ? initial[4] : endian::convert(initial[4]));
                    initial[5] = (endian!=endian::little ? initial[4] : endian::convert(initial[5]));
                    initial[6] = (endian!=endian::little ? initial[4] : endian::convert(initial[6]));
                    initial[7] = (endian!=endian::little ? initial[4] : endian::convert(initial[7]));
                    out.append((byte *) &initial[0], sizeof(uint32));
                    out.append((byte *) &initial[1], sizeof(uint32));
                    out.append((byte *) &initial[2], sizeof(uint32));
                    out.append((byte *) &initial[3], sizeof(uint32));
                    out.append((byte *) &initial[4], sizeof(uint32));
                    out.append((byte *) &initial[5], sizeof(uint32));
                    out.append((byte *) &initial[6], sizeof(uint32));
                    out.append((byte *) &initial[7], sizeof(uint32));
                    return out;
                }
            }
        }
    }
}

