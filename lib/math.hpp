#ifndef _STKLIB_MATH_HPP
# define _STKLIB_MATH_HPP

# include <vector>
# include <cstddef>

namespace StK {

template <typename Type> 
Type gcd(Type x, Type y) {
    int c = 0;
    if (x < y) std::swap(x, y);
    while (y) {
        if (x & 1) {
            if (y & 1) {
                x -= y;
                if (x < y) std::swap(x, y);
            } else {
                y >>= 1;
            }
        } else {
            if (y & 1) {
                x >>= 1;
                if (x < y) std::swap(x, y);
            } else {
                x >>= 1;
                y >>= 1;
                ++c;
            }
        }
    }
    return x << c;
}

template <typename ModType>
std::vector<ModType> get_factorial(size_t n) {
    std::vector<ModType> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
    return fac;
}

template <typename ModType>
std::vector<ModType> get_factorial_inverse(size_t n, ModType fac_n) {
    std::vector<ModType> fac_inv(n + 1);
    fac_inv[n] = fac_n.inv();
    for (int i = n; i >= 1; --i) fac_inv[i - 1] = fac_inv[i] * i;
    return fac_inv;
}

template <typename ModType>
std::pair<std::vector<ModType>, std::vector<ModType> > get_factorial_and_inverse(size_t n) {
    auto fac = get_factorial<ModType>(n);
    return std::make_pair(fac, get_factorial_inverse(n, fac.back()));
}

template <typename Type>
Type ex_gcd(Type a, Type b, Type &x, Type &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    Type d = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

template <typename Type>
constexpr Type phi(Type x) {
    Type ans = 1;
    for (Type i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            x /= i;
            ans *= i - 1;
            while (x % i == 0) x /= i, ans *= i;
        }
    }
    if (x > 1) ans *= x - 1;
    return ans;
}

};

#endif
