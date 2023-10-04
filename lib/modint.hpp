#ifndef _STKLIB_MODINT_HPP
# define _STKLIB_MODINT_HPP

namespace StK {

template <typename Type, Type P, typename MulType = Type>
class ModInt {
   public:
    typedef Type DataType;
    
    static constexpr Type MOD = P;

   protected:
    Type x;

   public:
    template <typename ProType>
    class Protected {
       protected:
        ModInt &data;
       public:
        Protected(ModInt &data) : data(data) {}
        ModInt &replace(ProType a) { return data.replace(a); }
    };
    
    constexpr ModInt() : x(0) {}
    constexpr ModInt(Type c) : x(c) {}
    explicit constexpr operator Type() const { return x; }
    explicit constexpr operator bool() const { return x != 0; }
    constexpr bool operator!() const { return x == 0; }
    constexpr Type &data() { return x; }
    constexpr const Type data() const { return x; }
    template <typename ProType>
    constexpr ModInt &replace(ProType a) { return x = (a %= P) < 0 ? a + P : a, *this; }
    template <typename ProType = Type>
    Protected<ProType> protect() const { return *this; }
    friend constexpr ModInt operator+(ModInt a, const ModInt b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend constexpr ModInt operator-(ModInt a, const ModInt b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend constexpr ModInt operator*(ModInt a, const ModInt b) { return MulType(a.x) * b.x % P; }
    constexpr ModInt &operator+=(const ModInt b) { return (x += b.x) >= P ? x -= P, *this : *this; }
    constexpr ModInt &operator-=(const ModInt b) { return (x -= b.x) < 0 ? x += P, *this : *this; }
    constexpr ModInt &operator*=(const ModInt b) { return x = MulType(x) * b.x % P, *this; }
    template <typename ExpType> constexpr ModInt pow(ExpType exp) const { 
        ModInt base(*this), ans(exp & 1 ? base : ModInt(1));
        while (exp >>= 1) if (base *= base, exp & 1) ans *= base; return ans;
    }
    template <typename ExpType> constexpr ModInt &pows(ExpType exp) { return *this = pow(exp); }
    constexpr ModInt inv() const { return pow(P - 2); }
    constexpr ModInt operator~() const { return inv(); }
    constexpr ModInt &invs() { return pows(P - 2); }
    friend constexpr ModInt operator/(ModInt a, const ModInt b) { return a * ~b; }
    constexpr ModInt &operator/=(const ModInt b) { return operator*=(~b); }
    constexpr ModInt &operator++() { return operator+=(1); }
    constexpr ModInt &operator--() { return operator-=(1); }
    constexpr ModInt operator++(int) { ModInt Tmp = *this; return operator++(), Tmp; }
    constexpr ModInt operator--(int) { ModInt Tmp = *this; return operator--(), Tmp; }
    constexpr ModInt operator+() const { return *this; }
    constexpr ModInt operator-() const { return ModInt(0) - *this; }
    constexpr bool operator==(const ModInt a) const { return x == Type(a); }
    constexpr bool operator!=(const ModInt a) const { return x != Type(a); }
    friend constexpr bool operator<(const ModInt a, const ModInt b) { return a.x < b.x; }
    friend constexpr bool operator>(const ModInt a, const ModInt b) { return a.x > b.x; }
    friend constexpr bool operator<=(const ModInt a, const ModInt b) { return a.x <= b.x; }
    friend constexpr bool operator>=(const ModInt a, const ModInt b) { return a.x >= b.x; }
# if __cpp_impl_three_way_comparison >= 201907L
    friend constexpr Type operator<=>(const ModInt a, const ModInt b) { return a.x - b.x; }
# endif

# ifdef _GLIBCXX_ISTREAM

    template <typename _CharT, class _Traits>
    friend std::basic_istream<_CharT, _Traits>&
    operator>>(std::basic_istream<_CharT, _Traits> &in_stream, ModInt &a) {
        return in_stream >> a.x;
    }

    template <typename ProType, typename _CharT, class _Traits>
    friend std::basic_istream<_CharT, _Traits>&
    operator>>(std::basic_istream<_CharT, _Traits> &in_stream, Protected<ProType> a) {
        ProType temp_protect;
        in_stream >> temp_protect;
        a.replace(temp_protect);
        return in_stream;
    }

# endif

# ifdef _GLIBCXX_OSTREAM

    template <typename _CharT, class _Traits>
    friend std::basic_ostream<_CharT, _Traits>&
    operator<<(std::basic_ostream<_CharT, _Traits> &out_stream, const ModInt a) {
        return out_stream << a.x;
    }

# endif

};

}  // namespace StK

#endif
