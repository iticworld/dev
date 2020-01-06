/**
 *
 * @author      novemberizing
 * @since       0.0.1
 * @date        2018. 7. 16.
 */

#ifndef   __NOVEMBERIZING__QUEUE__HH__
#define   __NOVEMBERIZING__QUEUE__HH__

#include <novemberizing/collection.hh>

namespace novemberizing
{
    template <typename T>
    class queue : protected collection<T>
    {
    public:     virtual void push(const T & o);
    public:     virtual void push(T && o);
    public:     virtual void pop();
    public:     virtual void pop(function<void (T&&)> f);
    public:     uint64 size() const override;
    public:     void size(function<void (uint64)> f) const override;
    public:     bool empty() const override;
    public:     void empty(function<void (bool)> f) const override;
    public:     void clear() override;
    public:     void clear(function<void (T &)> f);
    public:     queue<T> & operator=(const queue<T> & o);
    public:     queue<T> & operator=(queue<T> && o) noexcept;
    public:     queue();
    public:     queue(const queue<T> & o);
    public:     queue(queue<T> && o) noexcept;
    public:     virtual ~queue();
    };
}

#endif // __NOVEMBERIZING__QUEUE__HH__
