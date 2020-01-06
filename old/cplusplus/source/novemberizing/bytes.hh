/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__BYTES__HH__
#define   __NOVEMBERIZING__BYTES__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class bytes
    {
    public:     class to
                {
                public:     static int16 integer16(const bytes & o, uint64 offset);
                public:     static int32 integer32(const bytes & o, uint64 offset);
                public:     static int64 integer64(const bytes & o, uint64 offset);
                public:     static uint16 uinteger16(const bytes & o, uint64 offset);
                public:     static uint32 uinteger32(const bytes & o, uint64 offset);
                public:     static uint64 uinteger64(const bytes & o, uint64 offset);
                public:     static int16 integer16(const bytes & o, uint64 offset, bool invert);
                public:     static int32 integer32(const bytes & o, uint64 offset, bool invert);
                public:     static int64 integer64(const bytes & o, uint64 offset, bool invert);
                public:     static uint16 uinteger16(const bytes & o, uint64 offset, bool invert);
                public:     static uint32 uinteger32(const bytes & o, uint64 offset, bool invert);
                public:     static uint64 uinteger64(const bytes & o, uint64 offset, bool invert);
                public:     to & operator=(const to & o);
                public:     to & operator=(to && o) noexcept;
                public:     to();
                public:     to(const to & o);
                public:     to(to && o) noexcept;
                public:     virtual ~to();
                };
    public:     static bytes sub(const bytes & o);
    public:     static bytes sub(const bytes & o, uint64 offset);
    public:     static bytes sub(const bytes & o, uint64 offset, uint64 n);
    public:     static const uint64 page;
    protected:  uint64 __capacity;
    protected:  uint64 __size;
    protected:  byte * __data;
    public:     uint64 capacity() const;
    public:     uint64 size() const;
    public:     const byte * v(uint64 i) const;
    public:     const byte * v() const;
    public:     byte & at(uint64 i);
    public:     const byte & at(uint64 i) const;
    public:     bytes & assign(const bytes & o);
    public:     bytes & assign(const bytes & o, uint64 pos);
    public:     bytes & assign(const bytes & o, uint64 pos, uint64 len);
    public:     bytes & assign(bytes && o) noexcept;
    public:     bytes & assign(const byte * s, uint64 len);
    public:     bytes & assign(byte c);
    public:     bytes & assign(byte c, uint64 len);
    public:     bytes & append(const bytes & o);
    public:     bytes & append(const bytes & o, uint64 pos);
    public:     bytes & append(const bytes & o, uint64 pos, uint64 len);
    public:     bytes & append(bytes && o);
    public:     bytes & append(const byte * s, uint64 len);
    public:     bytes & append(byte c);
    public:     bytes & append(byte c, uint64 len);
    public:     bytes & insert(uint64 offset, const bytes & o);
    public:     bytes & insert(uint64 offset, const bytes & o, uint64 pos);
    public:     bytes & insert(uint64 offset, const bytes & o, uint64 pos, uint64 len);
    public:     bytes & insert(uint64 offset, bytes && o);
    public:     bytes & insert(uint64 offset, const byte * s, uint64 len);
    public:     bytes & insert(uint64 offset, byte c);
    public:     bytes & insert(uint64 offset, byte c, uint64 len);
    public:     bytes & replace(uint64 offset, uint64 n, const bytes & o);
    public:     bytes & replace(uint64 offset, uint64 n, const bytes & o, uint64 pos);
    public:     bytes & replace(uint64 offset, uint64 n, const bytes & o, uint64 pos, uint64 len);
    public:     bytes & replace(uint64 offset, uint64 n, bytes && o);
    public:     bytes & replace(uint64 offset, uint64 n, const byte * s, uint64 len);
    public:     bytes & replace(uint64 offset, uint64 n, byte c);
    public:     bytes & replace(uint64 offset, uint64 n, byte c, uint64 len);
    public:     bytes & erase();
    public:     bytes & erase(uint64 offset);
    public:     bytes & erase(uint64 offset, uint64 n);
    public:     bytes & clear();
    public:     bytes & operator=(const bytes & o);
    public:     bytes & operator=(bytes && o) noexcept;
    public:     bytes & operator=(byte c);
    public:     bytes & operator+=(const bytes & o);
    public:     bytes & operator+=(bytes && o);
    public:     bytes & operator+=(byte c);
    public:     byte & operator[](uint64 i);
    public:     const byte & operator[](uint64 i) const;
    public:     bytes(int16 n);
    public:     bytes(int32 n);
    public:     bytes(int64 n);
    public:     bytes(uint16 n);
    public:     bytes(uint32 n);
    public:     bytes(uint64 n);
    public:     bytes();
    public:     bytes(const bytes & o);
    public:     bytes(const bytes & o, uint64 pos);
    public:     bytes(const bytes & o, uint64 pos, uint64 len);
    public:     bytes(bytes && o) noexcept;
    public:     bytes(const byte * s, uint64 len);
    public:     bytes(byte c);
    public:     bytes(byte c, uint64 len);
    public:     virtual ~bytes();
    };
}

#endif // __NOVEMBERIZING__BYTES__HH__
