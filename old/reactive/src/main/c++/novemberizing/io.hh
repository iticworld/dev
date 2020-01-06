#ifndef   __NOVEMBERIZING__IO__HH__
#define   __NOVEMBERIZING__IO__HH__

namespace novemberizing { namespace io {

typedef enum __EventType {
    Read  = 0x00000001 <<  0,
    Write = 0x00000001 <<  1,
    Close = 0x00000001 <<  2,
} EventType;

} }

#endif // __NOVEMBERIZING__IO__HH__
