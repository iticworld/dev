#ifndef   __NOVEMBERIZING_IO__BUFFER__INLINE__HH__
#define   __NOVEMBERIZING_IO__BUFFER__INLINE__HH__

#include <novemberizing/io/buffer.hh>

namespace novemberizing { namespace io {

/**
 * @fn          inline buffer::buffer(void)
 * @brief       default constructor of ds::buffer
 * @details
 */
inline Buffer::Buffer(void)
{
    __page = 0;
}

/**
 * @fn          inline buffer::~buffer(void)
 * @brief       destructor of ds::buffer
 * @details
 */
inline Buffer::~Buffer(void)
{
    __page = 0;
}

/**
 * @fn          inline type::size buffer::page(void) const
 * @brief       get page size
 * @details
 * @return      | type::size | - |
 */
inline type::size Buffer::page(void) const
{
    return __page;
}

/**
 * @fn          inline void buffer::page(type::size value)
 * @brief       set page size
 * @details
 * @param [in]  | value | type::size | - | ... |
 */
inline void Buffer::page(type::size value)
{
    __page = value;
}

} }

#endif // __NOVEMBERIZING_IO__BUFFER__INLINE__HH__
