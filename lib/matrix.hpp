#ifndef _STKLIB_MATRIX_HPP
# define _STKLIB_MATRIX_HPP

# include <stddef.h>

namespace StK {

template <typename Type, size_t SN, size_t SM>
class Matrix {
   public:
    using CurrentType = Matrix<Type, SN, SM>;
    using ThisType = CurrentType;

   protected:
    Type Data[SN][SM];

   public:
    inline constexpr Matrix() {
        for (size_t i = 0; i < SN; ++i) {
            for (size_t j = 0; j < SM; ++j) {
                Data[i][j] = 0;
            }
        }
    }
    inline constexpr Matrix(const Type x) {
        for (size_t i = 0; i < SN; ++i) {
            for (size_t j = 0; j < SM; ++j) {
                Data[i][j] = 0;
            }
        }
        for (size_t i = 0; i < SN && i < SM; ++i) Data[i][i] = x;
    }
    inline constexpr Matrix(const Type Source[SN][SM]) {
        for (size_t i = 0; i < SN; ++i) {
            for (size_t j = 0; j < SM; ++j) {
                Data[i][j] = Source[i][j];
            }
        }
    }
    inline constexpr Type *operator[](size_t x) { return Data[x]; }
};

template <typename Type, size_t SN, size_t SM>
inline constexpr bool operator==(Matrix<Type, SN, SM> A, Matrix<Type, SN, SM> B) {
    for (size_t i = 0; i < SN; ++i) {
        for (size_t j = 0; j < SM; ++j) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename Type, size_t SN, size_t SM>
inline constexpr Matrix<Type, SN, SM> operator+(Matrix<Type, SN, SM> A, Matrix<Type, SN, SM> B) {
    Matrix<Type, SN, SM> C;
    for (size_t i = 0; i < SN; ++i) {
        for (size_t j = 0; j < SM; ++j) C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}

template <typename Type, size_t SN, size_t SM>
inline constexpr Matrix<Type, SN, SM> operator-(Matrix<Type, SN, SM> A, Matrix<Type, SN, SM> B) {
    Matrix<Type, SN, SM> C;
    for (size_t i = 0; i < SN; ++i) {
        for (size_t j = 0; j < SM; ++j) C[i][j] = A[i][j] - B[i][j];
    }
    return C;
}

template <typename Type, size_t SN, size_t SK, size_t SM>
inline constexpr Matrix<Type, SN, SM> operator*(Matrix<Type, SN, SK> A, Matrix<Type, SK, SM> B) {
    Matrix<Type, SN, SM> Ret;
    for (size_t i = 0; i < SN; ++i) {
        for (size_t k = 0; k < SK; ++k) {
            for (size_t j = 0; j < SM; ++j) Ret[i][j] += A[i][k] * B[k][j];
        }
    }
    return Ret;
}

template <typename Type, size_t SN, typename ExpType>
inline Matrix<Type, SN, SN> pow(Matrix<Type, SN, SN> base, ExpType exp) {
    Matrix<Type, SN, SN> now(exp & 1 ? base : Matrix<Type, SN, SN>(1));
    while (exp >>= 1) if (base = base * base, exp & 1) now = now * base;
    return now;
}

}  // namespace StK

#endif
