/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__EVENT__HH__
#define   __NOVEMBERIZING__EVENT__HH__

#include <novemberizing.hh>
#include <novemberizing/input.hh>
#include <novemberizing/array/list.hh>
#include <novemberizing/queue.hh>

namespace novemberizing
{
    class event : public input
    {
    public:     class generator
                {

                };
    public:     class executor
                {
                public:     virtual void run();
                public:     executor & operator=(const executor & o);
                public:     executor & operator=(executor && o) noexcept;
                public:     executor();
                public:     executor(const executor & o);
                public:     executor(executor && o) noexcept;
                public:     virtual ~executor();
                };
    public:     class handler
                {

                };
    public:     class engine
                {
                protected:  static executor __executor;
                protected:  static array::list<handler *> __handlers;
                public:     static void run();
                public:     engine & operator=(const engine & o);
                public:     engine & operator=(engine && o) noexcept;
                public:     engine();
                public:     engine(const engine & o);
                public:     engine(engine && o) noexcept;
                public:     virtual ~engine();
                };
    protected:  uint32 __type;
    public:     event & operator=(const event & o);
    public:     event & operator=(event && o) noexcept;
    public:     event();
    public:     event(const event & o);
    public:     event(event && o) noexcept;
    public:     virtual ~event();
    };
}

#include <novemberizing/event.hp>
#include <novemberizing/event/engine.hp>
#include <novemberizing/event/executor.hp>

#endif // __NOVEMBERIZING__EVENT__HH__
