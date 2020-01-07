/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 7. 4.
 */

#ifndef   __NOVEMBERIZING__UUID__HH__
#define   __NOVEMBERIZING__UUID__HH__

#include <novemberizing.hh>
#include <novemberizing/timestamp.hh>
#include <novemberizing/bytes.hh>

namespace novemberizing
{
    class uuid
    {
    public:     static const uuid dns;
    public:     static const uuid url;
    public:     static const uuid oid;
    public:     static const uuid x500;
    public:     class is
                {
                public:     static bool v1(const uuid & o);
                public:     static bool v2(const uuid & o);
                public:     static bool v3(const uuid & o);
                public:     static bool v4(const uuid & o);
                public:     static bool v5(const uuid & o);
                public:     is & operator=(const is & o);
                public:     is & operator=(is && o) noexcept;
                public:     is();
                public:     is(const is & o);
                public:     is(is && o) noexcept;
                public:     virtual ~is();
                };
    public:     class to
                {
                public:     static novemberizing::timestamp timestamp(const uuid & o);
                public:     static novemberizing::bytes bytes(const uuid & o);
                public:     to & operator=(const to & o);
                public:     to & operator=(to && o) noexcept;
                public:     to();
                public:     to(const to & o);
                public:     to(to && o) noexcept;
                public:     virtual ~to();
                };
    public:     static const uuid nil;
    public:     static uint64 version(const uuid & v);
    protected:  static uint64 __node;
    protected:  uint64 __first;
    protected:  uint64 __second;
    public:     static uuid v1();
    public:     static uuid v1(int64 second);
    public:     static uuid v1(int64 second, int64 nano);
    public:     static uuid v1(const timestamp & o);
//    public:     static uuid v3(const string & v);
    public:     static uuid v3(const bytes & v);
//    public:     static uuid v3(const string & v, const uuid & id);
    public:     static uuid v3(const bytes & v, const uuid & id);
//    public:     static uuid v5(const string & v);
    public:     static uuid v5(const bytes & v);
//    public:     static uuid v5(const string & v, const uuid & id);
    public:     static uuid v5(const bytes & v, const uuid & id);
    public:     static uuid from(const bytes & v, const uuid & id, byte version);
    public:     static uuid from(const bytes & v, const uuid & id, byte version, function<bytes (const uuid &, const bytes &)> f);
//    public:     static uuid from(const string & v, const uuid & id, byte version);
//    public:     static uuid from(const string & v, const uuid & id, byte version, function<bytes (const uuid &, const string &)> f);
    public:     uint64 first() const;
    public:     uint64 second() const;
    public:     uuid & operator=(const uuid & o);
    public:     uuid & operator=(uuid && o) noexcept;
    public:     uuid(uint64 first, uint64 second) noexcept;
    public:     uuid();
    public:     uuid(const uuid & o);
    public:     uuid(uuid && o) noexcept;
    public:     virtual ~uuid();
    };
}

#include <novemberizing/uuid.hp>

#endif // __NOVEMBERIZING__UUID__HH__
