#ifndef _STKLIB_LINKMODINT_HPP
# define _STKLIB_LINKMODINT_HPP

namespace StK {

template <typename Type, Type &P, typename MulType = Type>
class LinkModInt {

   protected:
    Type x;

   public:
    template <typename ProType>
    class Protected {
       protected:
        LinkModInt &data;
       public:
        Protected(LinkModInt &data) : data(data) {}
        LinkModInt &replace(ProType a) { return data.replace(a); }
    };
    
    LinkModInt() : x(0) {}
    LinkModInt(Type c) : x(c) {}
    explicit operator Type() const { return x; }
    explicit operator bool() const { return x != 0; }
    bool operator!() const { return x == 0; }
    Type &data() { return x; }
    template <typename ProType>
    LinkModInt &replace(ProType a) { return x = (a %= P) < 0 ? a + P : a, *this; }
    template <typename ProType = Type>
    Protected<ProType> protect() { return *this; }
    friend LinkModInt operator+(LinkModInt a, const LinkModInt b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend LinkModInt operator-(LinkModInt a, const LinkModInt b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend LinkModInt operator*(LinkModInt a, const LinkModInt b) { return MulType(a.x) * b.x % P; }
    friend LinkModInt &operator+=(LinkModInt &a, const LinkModInt b) { return (a.x += b.x) >= P ? a.x -= P, a : a; }
    friend LinkModInt &operator-=(LinkModInt &a, const LinkModInt b) { return (a.x -= b.x) < 0 ? a.x += P, a : a; }
    friend LinkModInt &operator*=(LinkModInt &a, const LinkModInt b) { return a.x = MulType(a.x) * b.x % P, a; }
    template <typename ExpType> LinkModInt pow(ExpType exp) const { 
        LinkModInt base(*this), ans(exp & 1 ? base : LinkModInt(1));
        while (exp >>= 1) if (base *= base, exp & 1) ans *= base; return ans;
    }
    template <typename ExpType> LinkModInt &pows(ExpType exp) { return *this = pow(exp); }
    template <typename ExpType> friend LinkModInt pow(const LinkModInt x, ExpType exp) { return x.pow(exp); }
    template <typename ExpType> friend LinkModInt &pows(LinkModInt &x, ExpType exp) { return x.pows(exp); }
    LinkModInt inv() const { return pow(P - 2); }
    LinkModInt &invs() { return pows(P - 2); }
    friend LinkModInt inv(const LinkModInt x) { return x.inv(); }
    friend LinkModInt &invs(LinkModInt &x) { return x.invs(); }
    friend LinkModInt operator~(const LinkModInt x) { return x.inv(); }
    friend LinkModInt operator/(LinkModInt a, const LinkModInt b) { return a * ~b; }
    friend LinkModInt &operator/=(LinkModInt &a, const LinkModInt b) { return a *= ~b; }
    friend LinkModInt &operator++(LinkModInt &a) { return a += 1; }
    friend LinkModInt &operator--(LinkModInt &a) { return a -= 1; }
    friend LinkModInt operator++(LinkModInt &a, int) { LinkModInt Tmp = a; return a += 1, Tmp; }
    friend LinkModInt operator--(LinkModInt &a, int) { LinkModInt Tmp = a; return a -= 1, Tmp; }
    friend LinkModInt operator+(const LinkModInt a) { return a; }
    friend LinkModInt operator-(const LinkModInt a) { return 0 - a; }
    bool operator==(const LinkModInt a) const { return x == Type(a); }
    bool operator!=(const LinkModInt a) const { return x != Type(a); }
    friend bool operator<(const LinkModInt a, const LinkModInt b) { return a.x < b.x; }

# ifdef _GLIBCXX_ISTREAM

    template <typename _CharT, class _Traits>
    friend std::basic_istream<_CharT, _Traits>&
    operator>>(std::basic_istream<_CharT, _Traits> &in_stream, LinkModInt &a) {
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
    operator<<(std::basic_ostream<_CharT, _Traits> &out_stream, const LinkModInt a) {
        return out_stream << a.x;
    }

# endif

};

}  // namespace StK

#endif
