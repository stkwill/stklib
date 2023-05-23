#ifndef STK_MIAD
# define STK_MIAD

namespace StK {

template <typename Type1, typename Type2>
inline Type1 &mid(Type1 &x, const Type2 y) {
    return x < y ? x : x = y;
}

template <typename Type1, typename Type2>
inline Type1 &mad(Type1 &x, const Type2 y) {
    return x > y ? x : x = y;
}

template <typename Type1, typename Type2, typename... Args>
inline Type1 &mid(Type1 &x, const Type2 y, const Args... args) {
    return mid(mid(x, y), args...);
}

template <typename Type1, typename Type2, typename... Args>
inline Type1 &mad(Type1 &x, const Type2 y, const Args... args) {
    return mad(mad(x, y), args...);
}

# ifdef _GLIBCXX_ALGORITHM

using std::min;
using std::max;

# endif

} // namespace StK

#endif
