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
    
public:
    Matrix(int, int);
    Matrix(const Matrix& m);
    Matrix(int n): Matrix(n, n) { }
    Matrix(Corners, Corners);
    Matrix(Corners);
    ~Matrix();
    void lu(bool = true);
    Matrix forward_sub(Matrix);
    Matrix operator* (Matrix);
    void print();
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