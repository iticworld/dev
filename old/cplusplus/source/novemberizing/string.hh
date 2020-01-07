/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 07. 16.
 */

#ifndef   __NOVEMBERIZING__STRING__HH__
#define   __NOVEMBERIZING__STRING__HH__

#include <novemberizing.hh>

namespace novemberizing
{
    class string
    {
    public:     static const uint64 page;
    public:     static uint64 length(const char * s);
    public:     static char * create(const char * source);
    public:     static char * create(const char * source, uint64 len);
    public:     static char * create(char c);
    public:     static char * create(char c, uint64 len);
    public:     static char * reset(char * p, const char * source);
    public:     static char * reset(char * p, const char * source, uint64 len);
    public:     static char * reset(char * p, char c);
    public:     static char * reset(char * p, char c, uint64 len);
    public:     static string format(const char * fmt, ...);
    protected:  uint64 __capacity;
    protected:  uint64 __size;
    protected:  char * __data;
    public:     uint64 capacity() const;
    public:     uint64 size() const;
    public:     const char * v() const;
    public:     char & at(uint64 i);
    public:     const char & at(uint64 i) const;
    public:     string & assign(const string & o);
    public:     string & assign(const string & o, uint64 pos);
    public:     string & assign(const string & o, uint64 pos, uint64 len);
    public:     string & assign(string && o) noexcept;
    public:     string & assign(const char * s);
    public:     string & assign(const char * s, uint64 len);
    public:     string & assign(char c);
    public:     string & assign(char c, uint64 len);
    public:     string & append(const string & o);
    public:     string & append(const string & o, uint64 pos);
    public:     string & append(const string & o, uint64 pos, uint64 len);
    public:     string & append(string && o);
    public:     string & append(const char * s);
    public:     string & append(const char * s, uint64 len);
    public:     string & append(char c);
    public:     string & append(char c, uint64 len);
    public:     string & insert(uint64 offset, const string & o);
    public:     string & insert(uint64 offset, const string & o, uint64 pos);
    public:     string & insert(uint64 offset, const string & o, uint64 pos, uint64 len);
    public:     string & insert(uint64 offset, string && o);
    public:     string & insert(uint64 offset, const char * s);
    public:     string & insert(uint64 offset, const char * s, uint64 len);
    public:     string & insert(uint64 offset, char c);
    public:     string & insert(uint64 offset, char c, uint64 len);
    public:     string & replace(uint64 offset, uint64 n, const string & o);
    public:     string & replace(uint64 offset, uint64 n, const string & o, uint64 pos);
    public:     string & replace(uint64 offset, uint64 n, const string & o, uint64 pos, uint64 len);
    public:     string & replace(uint64 offset, uint64 n, string && o);
    public:     string & replace(uint64 offset, uint64 n, const char * s);
    public:     string & replace(uint64 offset, uint64 n, const char * s, uint64 len);
    public:     string & replace(uint64 offset, uint64 n, char c);
    public:     string & replace(uint64 offset, uint64 n, char c, uint64 len);
    public:     string & erase();
    public:     string & erase(uint64 offset);
    public:     string & erase(uint64 offset, uint64 n);
    public:     string & clear();
    public:     int compare(const string & o) const noexcept;
    public:     int compare(uint64 offset, uint64 n, const string & o) const;
    public:     int compare(uint64 offset, uint64 n, const string & o, uint64 pos, uint64 len) const;
    public:     int compare(const char * s) const;
    public:     int compare(uint64 offset, uint64 n, const char * s) const;
    public:     int compare(uint64 offset, uint64 n, const char * s, uint64 len) const;
    public:     bool equal(const string & o) const;
    public:     bool equal(string && o) const;
    public:     bool equal(const char * s) const;
    public:     bool equal(char c) const;
    public:     char & operator[](uint64 i);
    public:     const char & operator[](uint64 i) const;
    public:     string & operator=(const string & o);
    public:     string & operator=(string && o) noexcept;
    public:     string & operator=(const char * s);
    public:     string & operator=(char c);
    public:     string & operator+=(const string & o);
    public:     string & operator+=(string && o);
    public:     string & operator+=(const char * s);
    public:     string & operator+=(char c);
    public:     string();
    public:     string(const string & o);
    public:     string(const string & o, uint64 pos);
    public:     string(const string & o, uint64 pos, uint64 len);
    public:     string(string && o) noexcept;
    public:     string(const char * s);
    public:     string(const char * s, uint64 len);
    public:     string(char c);
    public:     string(char c, uint64 len);
    public:     virtual ~string();
    };

    inline bool operator==(const string & x, const string & y) noexcept;
    inline bool operator==(const char *   x, const string & y);
    inline bool operator==(const string & x, const char *   y);
    inline bool operator!=(const string & x, const string & y) noexcept;
    inline bool operator!=(const char *   x, const string & y);
    inline bool operator!=(const string & x, const char *   y);
    inline bool operator< (const string & x, const string & y) noexcept;
    inline bool operator< (const char *   x, const string & y);
    inline bool operator< (const string & x, const char *   y);
    inline bool operator<=(const string & x, const string & y) noexcept;
    inline bool operator<=(const char *   x, const string & y);
    inline bool operator<=(const string & x, const char *   y);
    inline bool operator> (const string & x, const string & y) noexcept;
    inline bool operator> (const char *   x, const string & y);
    inline bool operator> (const string & x, const char *   y);
    inline bool operator>=(const string & x, const string & y) noexcept;
    inline bool operator>=(const char *   x, const string & y);
    inline bool operator>=(const string & x, const char *   y);
}

#include <novemberizing/string.hp>

#endif // __NOVEMBERIZING__STRING__HH__
