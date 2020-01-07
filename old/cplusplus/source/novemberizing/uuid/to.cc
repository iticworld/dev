/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 5.
 */

#include "../uuid.hh"
#include "novemberizing.hh"
#include "novemberizing/exception.hh"

namespace novemberizing
{
    timestamp uuid::to::timestamp(const uuid & o)
    {
        if(!uuid::is::v1(o))
        {
            throw exception();
        }
        uint64 nanosecond = ((o.first() & 0xFFFFFFFF00000000UL) >> 32UL) |
                            ((o.first() & 0x00000000FFFF0000UL) << 16UL) |
                            ((o.first() & 0x0000000000000FFFUL) << 48UL);
        nanosecond -= 122192928000000000L;
        return novemberizing::timestamp(nanosecond/10000000, (nanosecond % 10000000) * 100);
    }

    novemberizing::bytes uuid::to::bytes(const uuid & o)
    {
        uint64 i = endian::convert(o.first());
        novemberizing::bytes n((byte *) &i, sizeof(uint64));
        i = endian::convert(o.second());
        n.append((byte *) &i, sizeof(uint64));
        return n;
    }
}

