/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 4.
 */

#include "uuid.hh"
#include "message/digest/v5.hh"
#include "secure/hash/algorithm/v1.hh"

#include <time.h>

namespace novemberizing
{
    uint64 uuid::__node = 0;
    const uuid uuid::nil(0, 0);
    const uuid uuid::dns (0x6ba7b8109dad11d1UL, 0x80b400c04fd430c8UL);
    const uuid uuid::url (0x6ba7b8119dad11d1UL, 0x80b400c04fd430c8UL);
    const uuid uuid::oid (0x6ba7b8129dad11d1UL, 0x80b400c04fd430c8UL);
    const uuid uuid::x500(0x6ba7b8149dad11d1UL, 0x80b400c04fd430c8UL);

    uint64 uuid::version(const uuid & v)
    {
        return (uint64) ((v.first() & 0xF000UL) >> 12UL);
    }

//    uuid uuid::from(const string & v, const uuid & id, byte version)
//    {
//        if(version == 3)
//        {
//            return from(v, id, version, [id](const uuid & base, const string & v){
//                bytes n = uuid::to::bytes(base);
//                n.append(v);
//                return message::digest::v5::from(n);
//            });
//        }
//        else if(version == 5)
//        {
//            return from(v, id, version, [](const uuid & base, const string & v){
//                bytes n = uuid::to::bytes(base);
//                n.append(v);
//                return secure::hash::algorithm::v1::from(n);
//            });
//        }
//        else
//        {
//            throw exception();
//        }
//    }
//
//    uuid uuid::from(const string & v, const uuid & id, byte version, function<bytes (const uuid &, const string &)> f)
//    {
//        if(f != nullptr)
//        {
//            if(version == 3 || version >= 5)
//            {
//                bytes digest = f(id, v);
//                digest[6] &= 0x0F;
//                digest[6] |= (version << 4U);
//                digest[8] &= 0x3F;
//                digest[8] |= 0x80;
//                return uuid(endian::convert(bytes::to::uinteger64(digest, 0)), endian::convert(bytes::to::uinteger64(digest, 8)));
//            }
//            else
//            {
//                throw exception();
//            }
//        }
//        else
//        {
//            throw exception();
//        }
//    }

    uuid uuid::from(const bytes & v, const uuid & id, byte version)
    {
        if(version == 3)
        {
            return from(v, id, version, [](const uuid & base, const bytes & v){
                bytes n = uuid::to::bytes(base);
                n.append(v);
                return message::digest::v5::from(n);
            });
        }
        else if(version == 5)
        {
            return from(v, id, version, [](const uuid & base, const bytes & v){
                bytes n = uuid::to::bytes(base);
                n.append(v);
                return secure::hash::algorithm::v1::from(n);
            });
        }
        else
        {
            throw exception();
        }
    }

    uuid uuid::from(const bytes & v, const uuid & id, byte version, function<bytes (const uuid & id, const bytes &)> f)
    {
        if(f != nullptr)
        {
            if(version == 3 || version >= 5)
            {
                bytes digest = f(id, v);
                digest[6] &= 0x0F;
                digest[6] |= (version << 4U);
                digest[8] &= 0x3F;
                digest[8] |= 0x80;
                return uuid(endian::convert(bytes::to::uinteger64(digest, 0)), endian::convert(bytes::to::uinteger64(digest, 8)));
            }
            else
            {
                throw exception();
            }
        }
        else
        {
            throw exception();
        }
    }

    uuid uuid::v1()
    {
#ifndef   WIN32
        struct timespec spec = {};

        if(clock_gettime(CLOCK_REALTIME, &spec) == -1)
        {
            throw exception();
        }

        return v1(spec.tv_sec, spec.tv_nsec);
#else  // WIN32
        throw exception();
#endif // WIN32
    }

    uuid uuid::v1(int64 second)
    {
#ifndef   WIN32
        struct timespec spec = {};

        if(clock_gettime(CLOCK_REALTIME, &spec) == -1)
        {
            throw exception();
        }

        return v1(second, spec.tv_nsec);
#else  // WIN32
        throw exception();
#endif // WIN32
    }

    uuid uuid::v1(int64 second, int64 nano)
    {
        throw exception();
//        if(__node == 0)
//        {
//            bytes mac = system::mac();
//            __node = ((uint64) mac.at(0) << 40UL) |
//                     ((uint64) mac.at(1) << 32UL) |
//                     ((uint64) mac.at(2) << 24UL) |
//                     ((uint64) mac.at(3) << 16UL) |
//                     ((uint64) mac.at(4) <<  8UL) |
//                     ((uint64) mac.at(5) <<  0UL);
//        }
//
//        int64 nanosecond = second * 10000000 + nano / 100 + 122192928000000000L;
//        uint64 time = (((uint64) nanosecond << 32UL) | (((uint64) nanosecond & 0xFFFF00000000UL) >> 16UL) | ((((uint64) nanosecond >> 48UL) & 0x0FFFUL) | 0x1000UL));
//        uint64 node = (((uint64) nano << 48UL) | __node);
//        return uuid(time, (node & 0x3FFFFFFFFFFFFFFFUL) | 0x8000000000000000UL);
    }

    uuid uuid::v1(const timestamp & o){ return v1(o.second(), o.nanosecond()); }

//    uuid uuid::v3(const string & v) { return from(v, url, 0x03); }
    uuid uuid::v3(const bytes & v) { return from(v, url, 0x03); }
//    uuid uuid::v3(const string & v, const uuid & id) { return from(v, id, 0x03); }
    uuid uuid::v3(const bytes & v, const uuid & id) { return from(v, id, 0x03); }

//    uuid uuid::v5(const string & v) { return from(v, url, 0x05); }
    uuid uuid::v5(const bytes & v) { return from(v, url, 0x05); }
//    uuid uuid::v5(const string & v, const uuid & id) { return from(v, id, 0x05); }
    uuid uuid::v5(const bytes & v, const uuid & id) { return from(v, id, 0x05); }
}
