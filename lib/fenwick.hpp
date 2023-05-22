#ifndef STK_FENWICK
# define STK_FENWICK

#include <functional>

namespace StK {

template <class Type, class PlusOper = std::plus<Type> >
class Fenwick {

   protected:
    size_t size;
    Type *data;

   public:
    template <class... Args>
      Fenwick(size_t size, Args... args)
      : size(size), data(new Type[size + 1](args...)) {}

    ~Fenwick() { delete[] data; }

    template <typename AddType>
    Fenwick &add(size_t i, AddType v) { while (i <= size) data[i] += v, i += i & -i; return *this; }
    Type sum(size_t i) { Type ans(*data); while (i) ans += data[i], i &= i - 1; return ans; }

};

} // namespace StK

#endif
