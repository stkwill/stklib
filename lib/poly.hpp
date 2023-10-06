#ifndef _STK_POLY_HPP
# define _STK_POLY_HPP

# include <cassert>
# include <cstdint>
# include <cstring>
# include <algorithm>
# include <vector>

# ifndef self
#  define self (*this)
# endif

namespace StK {

class BitReverse {

   public:
    typedef uint32_t size_type;
    static constexpr size_t BIT_LEN = 32;

   protected:
    std::vector<size_type> data;

   public:
    BitReverse() {}
    ~BitReverse() {}

    void reserve(const size_t new_size) {
        const size_t last_size = data.size();
        if (new_size <= last_size) return;
        data.resize(new_size);
        for (size_type u = last_size; u < new_size; ++u) {
            data[u] = data[u >> 1] >> 1 | size_type(u & 1) << BIT_LEN - 1;
        }
    }

    const size_type operator[](size_t u) { return data[u]; }

} bit_reverse;

template <typename ModType, typename ModType::DataType PrimRootRaw>
class ModuleSpace {

   public:
    typedef uint32_t size_type;

    static constexpr ModType primitive_root = PrimRootRaw;

   protected:
    class UnityRoot {
       
       protected:
        std::vector<ModType> data;

       public:
        UnityRoot() {}
        ~UnityRoot() {}

        void reserve(const size_t new_size) {
            size_t last_size = data.size();
            if (new_size << 1 <= last_size) return;
            data.resize(new_size << 1);
            ModType base = primitive_root.pow(ModType::MOD - 1 >> __builtin_ctz(new_size));
            ModType now = data[new_size] = 1;
            last_size = std::max(last_size, size_t(1));
            for (size_t i = new_size + 1; i < new_size << 1; ++i) data[i] = now *= base;
            for (size_t i = new_size - 1; i >= last_size; --i) data[i] = data[i << 1];
        }
       
        const ModType operator[](size_t i) { return data[i]; }

    };

   public:
    ModuleSpace() {}
    ~ModuleSpace() {}

    UnityRoot &get_unity_root() {
        static UnityRoot unity_root;
        return unity_root;
    }

    template <typename Sequence = std::vector<ModType> >
    class Poly : public Sequence {

       public:
        template <typename... Args>
        Poly(Args... args) : Sequence(args...) {}

        typedef uint32_t size_type;

        // resize self
        Poly &resizes(size_t n) { return self.resize(n), self; }

        // NTT self
        Poly &NTTs() {
            const size_type n = self.size();
            const size_type bit_len = __builtin_ctz(n);
            
            assert(n == size_type(1) << bit_len);
            assert(bit_len <= __builtin_ctz(ModType::MOD - 1));
            
            bit_reverse.reserve(n);
            ModuleSpace().get_unity_root().reserve(n);

            for (size_type u = 0; u < n; ++u) {
                size_type v = bit_reverse[u] >> bit_reverse.BIT_LEN - bit_len;
                if (v < u) std::swap(self[v], self[u]);
            }

            for (size_type i = 1; i < n; i <<= 1) {
                for (size_type j = 0; j < n; j += i << 1) {
                    for (size_type k = 0; k < i; ++k) {
                        ModType x = self[j | k];
                        ModType y = self[j | i | k] * ModuleSpace().get_unity_root()[i << 1 | k];
                        self[j | k] = x + y, self[j | i | k] = x - y;
                    }
                }
            }
            return self;
        }

        Poly NTT() { return Poly(self).NTTs(); }

        // INTT self
        Poly &INTTs() {
            self.NTTs();
            const size_type n = self.size();
            ModType inverse = ModType(n).inv();
            for (auto &x : self) x *= inverse;
            std::reverse(self.begin() + 1, self.end());
            return self;
        }
        
        Poly INTT() { return Poly(self).INTTs(); }

        friend Poly operator+(Poly a) { return a; }
        friend Poly operator-(Poly a) {
            for (auto &x : a) x = -x;
            return a;
        }

        Poly &operator++() { return assert(self.size()), ++self[0], self; }
        Poly &operator--() { return assert(self.size()), --self[0], self; }
        Poly &operator+=(ModType b) { return assert(self.size()), self[0] += b, self; }
        Poly &operator-=(ModType b) { return assert(self.size()), self[0] -= b, self; }
        friend Poly operator+(Poly a, ModType b) { return a += b; }
        friend Poly operator+(ModType a, Poly b) { return b += a; }
        friend Poly operator-(Poly a, ModType b) { return a -= b; }
        friend Poly operator-(ModType a, Poly b) { return -b += a; }

        Poly &operator+=(Poly b) {
            if (self.size() < b.size()) self.swap(b);
            for (size_t i = 0; i < b.size(); ++i) self[i] += b[i];
            return self;
        }

        friend Poly operator+(Poly a, Poly b) { return a += b; }

        Poly &operator-=(Poly b) {
            if (self.size() < b.size()) self.resize(b.size());
            for (size_t i = 0; i < b.size(); ++i) self[i] -= b[i];
            return self;
        }

        friend Poly operator-(Poly a, Poly b) { return a -= b; }

        Poly &operator*=(ModType b) {
            for (auto &x : self) x *= b;
            return self;
        }

        friend Poly operator*(Poly a, ModType b) { return a *= b; }
        friend Poly operator*(ModType a, Poly b) { return b *= a; }

        friend Poly &operator*=(Poly &a, Poly b) {
            if (a.empty() || b.empty()) return a = Poly();
            size_t na = a.size(), nb = b.size(), nc = na + nb - 1, n = 1 << std::__lg(nc - 1) + 1;
            a.resizes(n).NTTs();
            b.resizes(n).NTTs();
            for (size_t i = 0; i < n; ++i) a[i] *= b[i];
            return a.INTTs().resizes(nc);
        }
        
        friend Poly operator*(Poly a, Poly b) { return a *= b; }

        // sqr self
        Poly &sqrs() {
            size_t na = self.size(), nb = na, nc = na + nb - 1, n = 1 << std::__lg(nc - 1) + 1;
            self.resizes(n).NTTs();
            for (size_t i = 0; i < n; ++i) self[i] *= self[i];
            return self.INTTs().resizes(nc);
        }

        Poly sqr() { return Poly(self).sqrs(); }

        // inv self
        Poly &invs() {
            assert(self.size());
            size_t n = self.size();
            if (n == 1) return self[0].invs(), self;
            assert(n > 0);
            size_t m = n + 1 >> 1;
            size_t max_n = 1 << std::__lg(m + m - 1 + n - 1 - 1) + 1;
            Poly a(self.begin(), self.begin() + m);
            a.invs().resizes(max_n).NTTs();
            self.resizes(max_n).NTTs();
            for (size_t i = 0; i < max_n; ++i) self[i] = a[i] + a[i] - a[i] * a[i] * self[i];
            return self.INTTs().resizes(n);
        }

        Poly inv() { return Poly(self).invs(); }

        Poly &operator/=(Poly b) { return self *= b.invs(); }

        Poly operator/(Poly b) { return Poly(self) /= b; }

        // differentiation self
        Poly &diffs() {
            if (self.empty()) return self;
            for (int i = 1; i < self.size(); ++i) self[i - 1] = self[i] * i;
            self.pop_back();
            return self;
        }

        Poly diff() { return Poly(self).invs(); }

        // integrate self
        Poly &intes() {
            self.insert(self.begin(), ModType(0));
            Poly inv(self.size());
            inv[0] = inv[1] = 1;
            for (int i = 2; i < self.size(); ++i) {
                self[i] *= inv[i] = -ModType(ModType::MOD / i) * inv[ModType::MOD % i];
            }
            return self;
        }

        Poly inte() { return Poly(self).intes(); }

        // ln self
        Poly &lns() {
            size_t n = self.size();
            assert(n > 0);
            assert(self[0] != 0);
            Poly pinv = self.inv();
            return (self.diffs() *= pinv).resizes(n - 1).intes();
        }

        Poly ln() { return Poly(self).lns(); }

        // exp self
        Poly &exps() {
            size_t n = self.size();
            assert(n > 0);
            if (n == 1) return assert(self[0] == 0), self[0] = 1, self;
            size_t m = n + 1 >> 1;
            Poly a(self.begin(), self.begin() + m);
            a.exps();
            return (++(self -= Poly(a).resizes(n).lns()) *= a).resizes(n);
        }

        Poly exp() { return Poly(self).exps(); }

    };

};

}  // namespace StK

#endif
