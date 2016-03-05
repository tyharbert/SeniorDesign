#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <iostream>
#include <iomanip>

#include "utils.hpp"
#include "corner.hpp"

// forward declaration of helper structs
struct Range;

class Matrix {
private:
    float** _values;
    int _height;
    int _width;
    void gauss(Range, int);
    void gauss_app(Range, Range);
    int inf_norm(Range, int);
    void row_swap(int, int, Range);
    void deallocate_values();
    
public:
    Matrix(int, int);
    Matrix(const Matrix& m);
    Matrix(int n): Matrix(n, n) { }
    Matrix(Corners, Corners);
    Matrix(Corners);
    Matrix(int*, int);
    ~Matrix();
    Matrix lu(bool = true);
    Matrix forward_sub(const Matrix&);
    Matrix back_sub(const Matrix&);
    void reshape(int, int, int = 1);
    Matrix operator* (const Matrix&);
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

struct Range
{
    int start;
    int end;
    Range(int s, int e): start(s), end(e) { assert_le(start, end); }
    Range(int p): Range(p, p) { }
    int length() { return (2+end) - (1+start); }
};

#endif