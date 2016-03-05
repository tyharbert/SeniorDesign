#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <iostream>
#include <iomanip>

#include "utils.hpp"
#include "corner.hpp"

// forward declaration of helper structs
struct Range;

template<typename T>
class Matrix {
private:
    T** _values;
    int _height;
    int _width;
    void gauss(Range, int);
    void gauss_app(Range, Range);
    int inf_norm(Range, int);
    void row_swap(int, int, Range);
    void deallocate_values();
    
public:
    Matrix(int, int);
    Matrix(const Matrix<T>& m);
    Matrix(int n): Matrix(n, n) { }
    Matrix(Corners, Corners);
    Matrix(Corners);
    Matrix(int*, int);
    Matrix(T, T);
    ~Matrix();
    Matrix<T> lu(bool = true);
    Matrix<T> forward_sub(const Matrix<T>&);
    Matrix<T> back_sub(const Matrix<T>&);
    void reshape(int, int, int = 1);
    Matrix<T> operator* (const Matrix<T>&);
    template<typename T1>
    friend std::ostream& operator<<(std::ostream&, const Matrix<T1>&);
};

// prints a matrix
template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    os << std::scientific << std::setprecision(4);
    for (int r=0; r < m._height; r++) {
        for (int c=0; c < m._width; c++) {
            os << m._values[r][c] << '\t';
        }
        os << std::endl;
    }

    return os;
}

struct Range
{
    int start;
    int end;
    Range(int s, int e): start(s), end(e) { assert_le(start, end); }
    Range(int p): Range(p, p) { }
    int length() { return (2+end) - (1+start); }
};

#endif