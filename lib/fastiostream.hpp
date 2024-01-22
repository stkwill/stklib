#ifndef _STKLIB_FASTIOSTREAM_HPP
# define _STKLIB_FASTIOSTREAM_HPP

# include <cstdio>
# include <cctype>
# include <limits>
# include <type_traits>
# include <string>

namespace StK {

class BasicFastFStream {

   protected:
    static constexpr int BUF_SIZE = 1 << 22;
    char buf[BUF_SIZE + 1];
    int buf_pos = 0;
    FILE *file;

   public:
    BasicFastFStream(FILE *f) : file(f) {}
    ~BasicFastFStream() = default;

};

class FastOFStream : public BasicFastFStream {

   public:
    FastOFStream(FILE *f = stdout) : BasicFastFStream(f) {}
    ~FastOFStream() { flush(); }
    FastOFStream &flush() {
        std::fwrite(buf, 1, buf_pos, file);
        buf_pos = 0;
        return *this;
    }
    FastOFStream &set_file(FILE *f = stdout) {
        flush();
        file = f;
        return *this;
    }

   private:
    void __I_putchar(char ch) {
        if (buf[buf_pos++] = ch, buf_pos == BUF_SIZE) flush();
    }
    char *__I_get_write_int_sta() {
        static char sta[64];
        return sta;
    }
    template <typename Type>
    void __I_write_unsigned_int(Type x) {
        int top = 0;
        do {
            __I_get_write_int_sta()[top++] = x % 10;
            x /= 10;
        } while (x);
        while (top) __I_putchar('0' + __I_get_write_int_sta()[--top]);
    }
    template <typename Type>
    void __I_write_signed_int(Type x) {
        if (x >= 0) return __I_write_unsigned_int(x);
        int top = 0;
        do {
            __I_get_write_int_sta()[top++] = x % 10;
            x /= 10;
        } while (x);
        __I_putchar('-');
        while (top) __I_putchar('0' - __I_get_write_int_sta()[--top]);
    }

   public:
    FastOFStream &operator<<(char x) {
        return __I_putchar(x), *this;
    }
    FastOFStream &operator<<(const char *s) {
        while (*s) __I_putchar(*(s++));
        return *this;
    }

# ifdef _GLIBCXX_STRING
    
    FastOFStream &operator<<(const std::string s) {
        for (auto ch : s) __I_putchar(ch);
        return *this;
    }

# endif

    template <typename Type, typename std::enable_if_t<std::numeric_limits<Type>::is_signed, int> = 0>
    FastOFStream &operator<<(const Type &x) {
        __I_write_signed_int(x);
        return *this;
    }
    template <typename Type, typename std::enable_if_t<std::numeric_limits<Type>::is_integer &&
                    !std::numeric_limits<Type>::is_signed, int> = 0>
    FastOFStream &operator<<(const Type &x) {
        __I_write_unsigned_int(x);
        return *this;
    }

    FastOFStream &operator<<(FastOFStream &(*func)(FastOFStream &)) {
        return func(*this);
    }
    FastOFStream &operator<<(BasicFastFStream &(*func)(BasicFastFStream &)) {
        func(*this);
        return *this;
    }

} fout;

class FastIFStream : public BasicFastFStream {

   public:
    FastIFStream(FILE *f = stdin) : BasicFastFStream(f) { buf_pos = BUF_SIZE; }
    FastIFStream &flush() {
        buf[std::fread(buf, 1, BUF_SIZE, file)] = '\0';
        buf_pos = 0;
        return *this;
    }
    FastIFStream &set_file(FILE *f) {
        file = f;
        return *this;
    }

    FastIFStream &operator<<(FastIFStream &(*func)(FastIFStream &)) {
        return func(*this);
    }
    FastIFStream &operator<<(BasicFastFStream &(*func)(BasicFastFStream &)) {
        func(*this);
        return *this;
    }

   protected:
    char __I_getchar() {
        if (buf_pos == BUF_SIZE) flush();
        return buf[buf_pos++];
    }
    bool __I_getbufstr(std::string &s) {
        int front = buf_pos - 1;
        while (std::isgraph(buf[buf_pos])) ++buf_pos;
        s.append(buf + front, buf_pos - front);
        return buf_pos == BUF_SIZE;
    }
    
   public:
    FastIFStream &operator>>(char &x) {
        while (std::isspace(x = __I_getchar()));
        return *this;
    }
    FastIFStream &operator>>(char *s) {
        while (std::isspace(*s = __I_getchar()));
        while (std::isgraph(*s)) *(++s) = __I_getchar();
        *s = '\0';
        return *this;
    }

# ifdef _GLIBCXX_STRING

    FastIFStream &operator>>(std::string &s) {
        while (std::isspace(__I_getchar()));
        while (__I_getbufstr(s) && std::isgraph(__I_getchar()));
        return *this;
    }

# endif
    
    template <typename Type, typename std::enable_if_t<std::numeric_limits<Type>::is_integer, int> = 0>
    FastIFStream &operator>>(Type &x) {
        int ch, f = 0;
        while (std::isspace(ch = __I_getchar())) f = ch == '-';
        x = ch ^ '0';
        while (std::isdigit(ch = __I_getchar())) x = (x << 3) + (x << 1) + (ch ^ '0');
        x = f ? -x : x;
        return *this;
    }

} fin;

FastIFStream &flush(FastIFStream &st) { return st.flush(); }
FastOFStream &flush(FastOFStream &st) { return st.flush(); }
FastOFStream &endl(FastOFStream &st) { return st << '\n' << flush; }

}  // namespace StK

#endif
