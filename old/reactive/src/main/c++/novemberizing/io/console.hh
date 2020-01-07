#ifndef   __NOVEMBERIZING_IO__CONSOLE__HH__
#define   __NOVEMBERIZING_IO__CONSOLE__HH__

#include <novemberizing/io/descriptor.hh>
#include <novemberizing/io/buffers/continuous.hh>
#include <novemberizing/io/buffers/list.hh>

namespace novemberizing { namespace io {

class console
{
public:     class input : public Descriptor {
            public:     friend class console;
            private:    buffers::Continuous __buffer;
            public:     std::function<void(console::input & in,Buffer & buffer)> onRead;
            public:     inline virtual bool should(EventType type) const;
            public:     inline virtual buffers::Continuous & buffer(void);
            public:     inline virtual type::int64 read(void);
            public:     inline virtual type::int64 write(void);
            public:     inline virtual type::int64 write(const type::byte * bytes,type::size length);
            public:     inline virtual int open(void);
            public:     inline virtual int close(void);
            protected:  inline input(void);
            public:     inline virtual ~input(void);
            };
public:     class output : public Descriptor {
            public:     friend class console;
            private:    buffers::List __buffer;
            public:     inline virtual bool should(EventType type) const;
            public:     inline virtual buffers::List & buffer(void);
            public:     inline virtual type::int64 read(void);
            public:     inline virtual type::int64 write(void);
            public:     inline virtual type::int64 write(const type::byte * bytes,type::size length);
            public:     inline virtual int open(void);
            public:     inline virtual int close(void);
            public:     inline virtual console::output & append(const type::byte * bytes,type::size position = 0,type::size length = -1L);
            public:     inline virtual console::output & flush(void);
            public:     inline virtual console::output & operator<<(const Buffer & buf);
            public:     inline virtual console::output & operator<<(char c);
            public:     inline virtual console::output & operator<<(const char * str);
            public:     inline virtual console::output & operator<<(console::output & (*op)(console::output &));
            protected:  inline output(void);
            public:     inline virtual ~output(void);
            };
public:     inline static console::output & lock(console::output & o);
public:     inline static console::output & unlock(console::output & o);
public:     inline static console::output & endl(console::output & o);
public:     inline static console::output & flush(console::output & o);
public:     static console::input in;
public:     static console::output out;
protected:  console(void);
public:     virtual ~console(void);
};

} }

#include <novemberizing/io/console.inline.hh>
#include <novemberizing/io/console.input.inline.hh>
#include <novemberizing/io/console.output.inline.hh>

#endif // __NOVEMBERIZING_IO__CONSOLE__HH__
