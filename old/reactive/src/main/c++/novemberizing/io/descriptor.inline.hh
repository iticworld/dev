#ifndef   __NOVEMBERIZING_IO__DESCRIPTOR__INLINE__HH__
#define   __NOVEMBERIZING_IO__DESCRIPTOR__INLINE__HH__

namespace novemberizing { namespace io {

inline int Descriptor::v(void) const { return __descriptor; }
inline bool Descriptor::alive(void) const { return __descriptor>=0; }

inline void Descriptor::registered(type::uint32 v){ __registered = v; }
inline type::uint32 Descriptor::registered(void) const { return __registered; }

} }

#endif // __NOVEMBERIZING_IO__DESCRIPTOR__INLINE__HH__
