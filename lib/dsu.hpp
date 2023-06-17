#ifndef _STKLIB_DSU_HPP
# define _STKLIB_DSU_HPP

# include <cstddef>
# include <vector>

namespace StK {

class DSU {

   protected:
    std::vector<int> data;

   public:
    DSU(size_t n) : data(n, 0) { for (size_t i = 0; i < n; ++i) data[i] = i; }
    size_t find(size_t x) { return x == data[x] ? x : data[x] = find(data[x]); }
    bool merge(size_t x, size_t y) { return (x = find(x)) != (y = find(y)) ? data[y] = x, true : false; }

};

} // namespace StK

#endif
