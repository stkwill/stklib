#ifndef _STKLIB_FUNCTIONS_HPP
# define _STKLIB_FUNCTIONS_HPP
# if __cplusplus < 201402L
#  error require at least C++14
# endif

namespace StK {

// Precedence 1 (I, Left to Right)

// Scope resolution (I, Left to Right) (can't implement)
struct ScopeResolution;


// Precedence 2 (II, Left to Right)

// Suffix increase (II, Left to Right)
template <typename Type1>
struct SuffixIncrease {
    decltype(auto) operator()(Type1 x) { return x++; }
};

// Suffix decrease (II, Left to Right)
template <typename Type1>
struct SuffixDecrease {
    decltype(auto) operator()(Type1 x) { return x--; }
};

// Function cast (II, Left to Right)
template <typename Type, typename... Args>
struct FunctionCast {
    decltype(auto) operator()(Args... args) { return Type(args...); }
};

// Function call (II, Left to Right)
template <typename Type, typename... Args>
struct FunctionCall {
    decltype(auto) operator()(Type func, Args... args) { return func(args...); }
};

# if __cpp_multidimensional_subscript >= 202110L

// Subscript (II, Left to Right)
template <typename Type, typename... Args>
struct Subscript {
    decltype(auto) operator()(Type array, Args... args) { return array[args...]; }
};

# else

// Subscript (II, Left to Right)
template <typename Type, typename... Args>
struct Subscript {
    decltype(auto) operator()(Type array, Args... args) { return array[{args...}]; }
};

# endif

// Subscript (II, Left to Right)
template <typename Type, typename Arg>
struct Subscript<Type, Arg> {
    decltype(auto) operator()(Type array, Arg arg) { return array[arg]; }
};

// Member access (II, Left to Right) (can't implement)
struct MemberAccess;


// Precedence 3 (III, Right to Left)

// Prefix increase (Force &) (III, Right to Left)
template <typename Type>
struct PrefixIncrease {
    Type &operator()(Type &x) { return ++x; }
};

// Prefix decrease (Force &) (III, Right to Left)
template <typename Type>
struct PrefixDecrease {
    Type &operator()(Type &x) { return --x; }
};

// Unary plus (III, Right to Left)
template <typename Type>
struct UnaryPlus {
    decltype(auto) operator()(Type x) { return +x; }
};

// Unary minus (III, Right to Left)
template <typename Type>
struct UnaryMinus {
    decltype(auto) operator()(Type x) { return -x; }
};

// Logical NOT (III, Right to Left)
template <typename Type>
struct LogicalNOT {
    decltype(auto) operator()(Type x) { return !x; }
};

// Bitwise NOT (III, Right to Left)
template <typename Type>
struct BitwiseNOT {
    decltype(auto) operator()(Type x) { return ~x; }
};

// C-Style Cast (III, Right to Left)
template <typename Type, typename TypeR>
struct CStyleCast {
    decltype(auto) operator()(TypeR x) { return (Type)x; }
};

// Dereference (Force &) (III, Right to Left)
template <typename Type>
struct Dereference {
    decltype(auto) operator()(Type x) { return *x; }
};

// Address of (III, Right to Left)
template <typename Type>
struct Addressof {
    decltype(auto) operator()(Type x) { return &x; }
};

// Size of (III, Right to Left) (Unnecessary implement)
struct Sizeof;

# if __cpp_impl_coroutine >= 201902L

// Co-Await (III, Right to Left) (C++20)
struct CoAwait;

# endif

// Dynamic memory allocate (III, Right to Left)
struct DynamicMemoryAllocate;

// Dynamic memory deallocate (III, Right to Left)
struct DynamicMemoryDeallocate;


// Precedence 4 (IV, Left to Right)

// Pointer to member (IV, Left to Right) (can't implement)
struct PointertoMember;


// Precedence 5 (V, Left to Right)

// Multiply (V, Left to Right)
template <typename Type1, typename Type2>
struct Multiply {
    decltype(auto) operator()(Type1 x, Type2 y) { return x * y; }
};

// Divide (V, Left to Right)
template <typename Type1, typename Type2>
struct Divide {
    decltype(auto) operator()(Type1 x, Type2 y) { return x / y; }
};

// Module (V, Left to Right)
template <typename Type1, typename Type2>
struct Module {
    decltype(auto) operator()(Type1 x, Type2 y) { return x % y; }
};


// Precedence 6 (VI, Left to Right)

// Plus (VI, Left to Right)
template <typename Type1, typename Type2>
struct Plus {
    decltype(auto) operator()(Type1 x, Type2 y) { return x + y; }
};

// Minus (VI, Left to Right)
template <typename Type1, typename Type2>
struct Minus {
    decltype(auto) operator()(Type1 x, Type2 y) { return x - y; }
};


// Precedence 7 (VII, Left to Right)

// (Bitwise) Left shift (VII, Left to Right)
template <typename Type1, typename Type2>
struct LeftShift {
    decltype(auto) operator()(Type1 x, Type2 y) { return x << y; }
};

// (Bitwise) Right shift (VII, Left to Right)
template <typename Type1, typename Type2>
struct RightShift {
    decltype(auto) operator()(Type1 x, Type2 y) { return x >> y; }
};


// Precedence 8 (VIII, Left to Right)

# if __cpp_impl_three_way_comparison >= 201907L

// Three-way compare (VIII, Left to Right)
template <typename Type1, typename Type2>
struct ThreewayCompare {
    decltype(auto) operator()(Type1 x, Type2 y) { return x <=> y; }
};

# endif


// Precedence 9 (IX, Left to Right)

// Less than (IX, Left to Right)
template <typename Type1, typename Type2>
struct Less {
    decltype(auto) operator()(Type1 x, Type2 y) { return x < y; }
};

// Less than or equal to (IX, Left to Right)
template <typename Type1, typename Type2>
struct LessEqual {
    decltype(auto) operator()(Type1 x, Type2 y) { return x <= y; }
};

// Greater than (IX, Left to Right)
template <typename Type1, typename Type2>
struct Greater {
    decltype(auto) operator()(Type1 x, Type2 y) { return x > y; }
};

// Greater than or equal to (IX, Left to Right)
template <typename Type1, typename Type2>
struct GreaterEqual {
    decltype(auto) operator()(Type1 x, Type2 y) { return x >= y; }
};


// Precedence 10 (X, Left to Right)

// Equal (X, Left to Right)
template <typename Type1, typename Type2>
struct Equal {
    decltype(auto) operator()(Type1 x, Type2 y) { return x == y; }
};

// Not equal (X, Left to Right)
template <typename Type1, typename Type2>
struct NotEqual {
    decltype(auto) operator()(Type1 x, Type2 y) { return x != y; }
};


// Precedence 11 (XI, Left to Right)

// Bitwise AND (XI, Left to Right)
template <typename Type1, typename Type2>
struct BitwiseAND {
    decltype(auto) operator()(Type1 x, Type2 y) { return x & y; }
};


// Precedence 12 (XII, Left to Right)

// Bitwise XOR (XII, Left to Right)
template <typename Type1, typename Type2>
struct BitwiseXOR {
    decltype(auto) operator()(Type1 x, Type2 y) { return x ^ y; }
};


// Precedence 13 (XIII, Left to Right)

// Bitwise OR (XIII, Left to Right)
template <typename Type1, typename Type2>
struct BitwiseOR {
    decltype(auto) operator()(Type1 x, Type2 y) { return x | y; }
};


// Precedence 14 (XIV, Left to Right)

// Logical AND (XIV, Left to Right)
template <typename Type1, typename Type2>
struct LogicalAND {
    decltype(auto) operator()(Type1 x, Type2 y) { return x && y; }
};


// Precedence 15 (XV, Left to Right)

// Logical OR (XV, Left to Right)
template <typename Type1, typename Type2>
struct LogicalOR {
    decltype(auto) operator()(Type1 x, Type2 y) { return x || y; }
};


// Precedence 16 (XVI, Right to Left)

// Ternary conditional (XVI, Right to Left)
struct TernaryConditional;

// Throw (XVI, Right to Left)
struct Throw;

# if __cpp_impl_coroutine >= 201902L

// Co-Yield (XVI, Right to Left) (C++20)
struct CoYield;

# endif

// Assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct Assign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x = y; }
};

// Plus assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct PlusAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x += y; }
};

// Minus assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct MinusAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x -= y; }
};

// Multiply assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct MultiplyAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x *= y; }
};

// Divide assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct DivideAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x /= y; }
};

// Module assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct ModuleAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x %= y; }
};

// (Bitwise) Left shift assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct LeftShiftAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x <<= y; }
};

// (Bitwise) Right shift assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct RightShiftAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x >>= y; }
};

// Bitwise AND assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct BitwiseANDAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x &= y; }
};

// Bitwise OR assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct BitwiseORAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x |= y; }
};

// Bitwise XOR assign (Force &) (XVI, Right to Left)
template <typename Type1, typename Type2>
struct BitwiseXORAssign {
    decltype(auto) operator()(Type1 x, Type2 y) { return x ^= y; }
};


// Precedence 17 (XVII, Left to Right)

// Comma (XVII, Left to Right)
template <typename Type1, typename Type2>
struct Comma {
    decltype(auto) operator()(Type1 x, Type2 y) { return x, y; }
};

}  // namespace StK

#endif
