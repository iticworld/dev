/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 18.
 */

#ifndef   __NOVEMBERIZING__EVENT__HH__
#define   __NOVEMBERIZING__EVENT__HH__

#include <novemberizing.hh>
#include <novemberizing/runnable.hh>

namespace novemberizing
{
    class event
    {
    public:     class processor : public runnable
                {
                public:     processor & operator=(const processor & o)
                            {
                                FUNCTION_LOG("");
                                return *this;
                            }
                public:     processor & operator=(processor && o) noexcept
                            {
                                FUNCTION_LOG("");
                                return *this;
                            }
                public:     processor()
                            {
                                FUNCTION_LOG("");
                            }
                public:     processor(const processor & o)
                            {
                                FUNCTION_LOG("");
                            }
                public:     processor(processor && o) noexcept
                            {
                                FUNCTION_LOG("");
                            }
                public:     virtual ~processor()
                            {
                                FUNCTION_LOG("");
                            }
                };
    public:     class engine
                {
                private:    static bool __cancel;
                private:    static processor __processor;
                public:     static void run()
                            {
                                while(!__cancel)
                                {
                                    __processor.turn();
                                }
                            }
                public:     engine & operator=(const engine & o)
                            {
                                FUNCTION_LOG("");
                                return *this;
                            }
                public:     engine & operator=(engine && o) noexcept
                            {
                                FUNCTION_LOG("");
                                return *this;
                            }
                public:     engine()
                            {
                                FUNCTION_LOG("");
                            }
                public:     engine(const engine & o)
                            {
                                FUNCTION_LOG("");
                            }
                public:     engine(engine && o) noexcept
                            {
                                FUNCTION_LOG("");
                            }
                public:     virtual ~engine()
                            {
                                FUNCTION_LOG("");
                            }
                };
    protected:  type::uint32 __id;
    public:     type::uint32 id() const { return __id; }
    public:     event & operator=(const event & o)
                {
                    if(&o != this)
                    {
                        __id = o.__id;
                    }
                    return *this;
                }
    public:     event & operator=(event && o) noexcept
                {
                    if(&o != this)
                    {
                        __id = o.__id;
                    }
                    return *this;
                }
    public:     event() : __id(0)
                {

                }
    public:     event(const event & o) : __id(o.__id)
                {
                    FUNCTION_LOG("");
                }
    public:     event(event && o) noexcept : __id(o.__id)
                {
                    o.__id = 0;
                }
    public:     virtual ~event()
                {
                    __id = 0;
                }
    };

    /**
     *
     * event::engine::run();
     */
}

#endif // __NOVEMBERIZING__EVENT__HH__
