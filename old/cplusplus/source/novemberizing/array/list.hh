/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#ifndef   __NOVEMBERIZING__ARRAY_LIST__HH__
#define   __NOVEMBERIZING__ARRAY_LIST__HH__

#include <novemberizing/list.hh>

namespace novemberizing
{
    namespace array
    {
        template <typename T>
        class list : public novemberizing::list<T>
        {
        protected:  T * __data;
        protected:  uint64 __max;
        protected:  uint64 __page;
        protected:  uint64 __size;
        protected:  uint64 __capacity;
        private:    static T * _construct(T * destination, const T * source, uint64 n);
        private:    static T * _construct(T * destination, const T & o);
        private:    static T * _construct(T * destination, T && o);
        private:    static T * _construct(T * destination, uint64 n, const T & o);
        private:    static T * _construct(T * destination, uint64 n, T && o);
        private:    static T * _destruct(T * destination);
        private:    static T * _destruct(T * destination, uint64 n);
        protected:  virtual uint64 previous(uint64 i);
        protected:  virtual uint64 next(uint64 i);
        protected:  virtual T & reference(uint64 i);
        protected:  virtual T * pointer(uint64 i);
        public:     virtual const T & get(uint64 i) const;
        public:     virtual T & get(uint64 i);
        public:     virtual void get(uint64 i, function<void (const T &)> f, function<void (const exception &)> e) const;
        public:     virtual void get(uint64 i, function<void (T &)> f, function<void (const exception &)> e);
        public:     virtual bool set(uint64 i, const T & o);
        public:     virtual bool set(uint64 i, T && o);
        public:     virtual void set(uint64 i, const T & o, function<void (bool)> f);
        public:     virtual void set(uint64 i, T && o, function<void (bool)> f);
        public:     virtual void set(uint64 i, const T & o, function<void (const T &)> f, function<void (const exception &)> e);
        public:     virtual void set(uint64 i, T && o, function<void (const T &)> f, function<void (const exception &)> e);
        public:     virtual uint64 size() const;
        public:     virtual void size(function<void (int64)> f) const;
        public:     virtual bool empty() const;
        public:     virtual void empty(function<void (bool)> f) const;
        public:     virtual void clear();
        public:     virtual void clear(function<void (T &)> f);
        public:     virtual bool exist(const T & o) const;
        public:     virtual void exist(const T & o, function<void (bool)> f) const;
        public:     virtual bool exist(T && o) const;
        public:     virtual void exist(T && o, function<void (bool)> f) const;
        public:     virtual bool add(const T & o);
        public:     virtual bool add(T && o);
        public:     virtual void add(const T & o, function<void (bool)> f);
        public:     virtual void add(T && o, function<void (bool)> f);
        public:     virtual bool del(const T & o);
        public:     virtual bool del(T && o);
        public:     virtual void del(const T & o, function<void (bool)> f);
        public:     virtual void del(T && o, function<void (bool)> f);
        public:     virtual void del(const T & o, function<void (T &)> f, function<void (const exception &)> e);
        public:     virtual void del(T && o, function<void (T &)> f, function<void (const exception &)> e);
        public:     virtual void each(function<void (const T &)> f) const;
        public:     virtual iterator<T> begin();
        public:     virtual iterator<T> end();
        public:     virtual const iterator<T> begin() const;
        public:     virtual const iterator<T> end() const;
        public:     list<T> & operator=(const list<T> & o);
        public:     list<T> & operator=(list<T> && o) noexcept;
        public:     T & operator[](uint64 i);
        public:     const T & operator[](uint64 i) const;
        public:     list(uint64 size, const T & v);
        public:     list();
        public:     list(const list<T> & o);
        public:     list(list<T> && o) noexcept;
        public:     ~list() override;
        };
    }
}

#include <novemberizing/array/list.hp>

#endif // __NOVEMBERIZING__ARRAY_LIST__HH__
