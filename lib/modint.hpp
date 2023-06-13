#ifndef _STKLIB_MODINT_HPP
# define _STKLIB_MODINT_HPP

namespace StK {

template <typename Type, Type P, typename MulType = Type>
class ModInt {

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
    
    ModInt() : x(0) {}
    ModInt(Type c) : x(c) {}
    explicit operator Type() const { return x; }
    explicit operator bool() const { return x != 0; }
    bool operator!() const { return x == 0; }
    Type &data() { return x; }
    template <typename ProType>
    ModInt &replace(ProType a) { return x = (a %= P) < 0 ? a + P : a, *this; }
    template <typename ProType = Type>
    Protected<ProType> protect() { return *this; }
    friend ModInt operator+(ModInt a, ModInt b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend ModInt operator-(ModInt a, ModInt b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend ModInt operator*(ModInt a, ModInt b) { return MulType(a.x) * b.x % P; }
    friend ModInt &operator+=(ModInt &a, ModInt b) { return (a.x += b.x) >= P ? a.x -= P, a : a; }
    friend ModInt &operator-=(ModInt &a, ModInt b) { return (a.x -= b.x) < 0 ? a.x += P, a : a; }
    friend ModInt &operator*=(ModInt &a, ModInt b) { return a.x = MulType(a.x) * b.x % P, a; }
    template <typename ExpType>
    ModInt pow(ExpType Exp) const { ModInt Base(*this), Ret(Exp & 1 ? Base : ModInt(1));
                                    while (Exp >>= 1) if (Base *= Base, Exp & 1) Ret *= Base; return Ret; }
    template <typename ExpType>
    ModInt &pows(ExpType Exp) { return *this = pow(Exp); }
    ModInt inv() const { return pow(P - 2); }
    ModInt &invs() { return pows(P - 2); }
    friend ModInt operator~(const ModInt x) { return x.inv(); }
    friend ModInt operator/(ModInt a, ModInt b) { return a * ~b; }
    friend ModInt &operator/=(ModInt &a, ModInt b) { return a *= ~b; }
    friend ModInt &operator++(ModInt &a) { return a += 1; }
    friend ModInt &operator--(ModInt &a) { return a -= 1; }
    friend ModInt operator++(ModInt &a, int) { ModInt Tmp = a; return a += 1, Tmp; }
    friend ModInt operator--(ModInt &a, int) { ModInt Tmp = a; return a -= 1, Tmp; }
    friend ModInt operator+(const ModInt a) { return a; }
    friend ModInt operator-(const ModInt a) { return 0 - a; }
    bool operator==(const ModInt a) const { return x == Type(a); }
    bool operator!=(const ModInt a) const { return x != Type(a); }
    friend bool operator<(const ModInt a, const ModInt b) { return a.x < b.x; }

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
