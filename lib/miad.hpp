#ifndef _STKLIB_MIAD_HPP
# define _STKLIB_MIAD_HPP

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

template <typename Type1, typename Type2>
inline Type1 min(const Type1 x, const Type2 y) {
    return x < y ? x : y;
}

template <typename Type1, typename Type2>
inline Type1 max(const Type1 x, const Type2 y) {
    return x > y ? x : y;
}

template <typename Type1, typename Type2, typename... Args>
inline Type1 min(const Type1 x, const Type2 y, const Args... args) {
    return min(min(x, y), args...);
}

template <typename Type1, typename Type2, typename... Args>
inline Type1 max(const Type1 x, const Type2 y, const Args... args) {
    return max(max(x, y), args...);
}

} // namespace StK

#endif
