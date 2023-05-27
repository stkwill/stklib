#ifndef _STKLIB_FENWICK_HPP
# define _STKLIB_FENWICK_HPP

# include <functional>

namespace StK {

template <class Type, class PlusOper = std::plus<Type>, class Sequence = std::vector<Type> >
class Fenwick {

   protected:
    size_t size;
    Sequence data;

   public:
    template <class... Args>
      Fenwick(size_t size, Args... args)
      : size(size), data(size + 1, Type(args...)) {}

    Fenwick &add(size_t i, Type v) { while (i <= size) data[i] = PlusOper()(data[i], v), i += i & -i; return *this; }

    Type sum(size_t i) { Type ans(data.front()); while (i) ans = PlusOper()(ans, data[i]), i &= i - 1; return ans; }

};

} // namespace StK

#endif
