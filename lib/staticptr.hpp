#ifndef _STKLIB_STATICPTR_HPP
# define _STKLIB_STATICPTR_HPP

namespace StK {

template <typename Type, Type *POOL, typename SizeType>
class StaticPtr {
   protected:
    SizeType x;

   public:
    explicit StaticPtr() : x() {}
    explicit StaticPtr(SizeType x) : x(x) {}
    explicit StaticPtr(Type *ptr) : x(ptr - POOL) {}
    explicit operator SizeType() { return x; }
    explicit operator bool() { return bool(x); }
    explicit operator Type*() { return POOL + x; }
    Type &operator*() { return POOL[x]; }
    Type *operator->() { return POOL + x; }
    friend bool operator==(StaticPtr a, StaticPtr b) { return a.x == b.x; }
    friend bool operator!=(StaticPtr a, StaticPtr b) { return a.x != b.x; }
};

}  // namespace StK

#endif
