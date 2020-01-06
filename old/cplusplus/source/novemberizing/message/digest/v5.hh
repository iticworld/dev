/**
 * md5 processes a variable length message into a fixed length output of 128 bits.
 * The input message is broken up into chunks of 512 bit blocks (sixteen 32-bit word);
 * the message is padded so that its length is divisible by 512.
 * The padding works as follows: first a single bit 1, is appended to the end of message.
 * This is followed by as many zeros as are required to bring the length of the message up to 64 bits
 * fewer than a multiple of 512.
 * The remaining bits are filled up with 64 bits representing the length of the original message, modulo 2^64.
 *
 * The main md5 algorithm operates on a 128 bit state, divided into four 32 bit words, denoted A, B, C, and D.
 * These are initialized to certain fixed constants.
 * The main algorithm then uses each 512 bit message block in turn to modify the state.
 * The processing of a message block consists of four similar stages, termed rounds, each round is composed
 * of 16 similar operations based on a non-linear function F, modular addition, and left rotation.
 *
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 3.
 */

#ifndef   __NOVEMBERIZING__MESSAGE_DIGEST_V5__HH__
#define   __NOVEMBERIZING__MESSAGE_DIGEST_V5__HH__

#include <novemberizing/string.hh>
#include <novemberizing/bytes.hh>

namespace novemberizing
{
    namespace message
    {
        namespace digest
        {
            class v5
            {
            public:     static const uint32 __shift[64];
            public:     static const uint32 __integer[64];
            public:     static const uint32 __initial[4];
//            public:     static bytes from(const string & v);
            public:     static bytes from(const bytes & v);
            public:     v5 & operator=(const v5 & o);
            public:     v5 & operator=(v5 && o) noexcept;
            public:     v5();
            public:     v5(const v5 & o);
            public:     v5(v5 && o) noexcept;
            public:     virtual ~v5();
            };
        }
    }
}

#include <novemberizing/message/digest/v5.hp>

#endif // __NOVEMBERIZING__MESSAGE_DIGEST_V5__HH__
