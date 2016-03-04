#include "matrix.hpp"

// matrix class constructor
Matrix::Matrix(int h, int w): _height(h), _width(w) {
    _values = new float*[h]();
    for (int i=0; i < h; i++)
        _values[i] = new float[w]();
}

// matrix copy constructor
Matrix::Matrix(const Matrix& m): Matrix(m._height, m._width) {
    for (int r=0; r < m._height; r++)
        for (int c=0; c < m._width; c++){
            _values[r][c] = m._values[r][c];
        }
}

// constructor for transformation matrix
Matrix::Matrix(Corners orig, Corners dest): Matrix(8) {
    int row;
    int* ox = orig.xArray();
    int* oy = orig.yArray();
    int* dx = dest.xArray();
    int* dy = dest.yArray();

    for (int i=0; i < 4; i++) {
        _values[i][0] = ox[i];
        _values[i][1] = oy[i];
        _values[i][2] = 1;
    }

    for (int i=0; i < 4; i++) {
        row = i+4;
        _values[row][3] = ox[i];
        _values[row][4] = oy[i];
        _values[row][5] = 1;
    }

    for (int i=0; i < 4; i++) {
        _values[i][6] = -((float)ox[i])*dx[i];
        _values[i][7] = -((float)oy[i])*dx[i];
    }

    for (int i=0; i < 4; i++) {
        row = i+4;
        _values[row][6] = -((float)ox[i])*dy[i];
        _values[row][7] = -((float)oy[i])*dy[i];
    }
}

// matrix destructor
Matrix::~Matrix() {
    for (int i=0; i < _height; i++)
        delete _values[i];
    delete _values;
}

// computes the LU decomposition
// of an NxN matrix
void Matrix::lu() {
    assert(_height == _width); // must be a square matrix
    int n = _height - 1;
    int mu;

    // int* p = new int[n]; // contains pivot values
    // for (int i = 0; i < n; i++)
    //     p[i] = -1;

    // partial pivot gaussian elimination
    for (int k = 0; k < n; k++) {
        mu = inf_norm(Range(k, n),k);
        row_swap(k, mu, Range(k, n));
        // p[k] = mu;

        if (_values[k][k] != 0) {
            gauss(Range(k+1, n), k);
            gauss_app(Range(k+1, n), Range(k+1, n));
        }
    }

    // set upper or lower values to 0
    for (int c = 0; c < n; c++)
        for (int r = c+1; r <= n; r++)
            _values[r][c] = 0;
}

// performs a Gauss Transform
// of the column over the range of rows supplied
void Matrix::gauss(Range rows, int col) {
    for (int r = rows.start; r <= rows.end; r++) { 
        _values[r][col] = _values[r][col]/_values[rows.start-1][col];
    }
}

// performs an NxN Gauss Transform
void Matrix::gauss_app(Range rows, Range cols) {
    assert(rows.length() == cols.length()); // must be a square matrix

    for (int c = cols.start; c <= cols.end ; c++) {
        for (int r = rows.start; r <= rows.end; r++) {
            _values[r][c] -= _values[r][cols.start-1]*_values[rows.start-1][c];
        }
    }
}

// finds the row location of the infinite norm of the values in a specified range
int Matrix::inf_norm(Range rows, int col) {
    float max = -1;
    float test;
    int row;
    
    for (int r = rows.start; r <= rows.end; r++) {
        test = (_values[r][col] < 0? -_values[r][col]: _values[r][col]); // absolute value
        if (test > max) {
            max = test;
            row = r;
        }
    }
    
    return row;
}

// swaps the values in one row with the values on another row
void Matrix::row_swap(int row1, int row2, Range cols) {
    if (row1 == row2) return; // don't swap for the same row

    for (int c = cols.start; c <= cols.end; c++) {
        std::swap(_values[row1][c], _values[row2][c]);
    }
}

// multiplies two matricies
// axb * bxc = axc
Matrix Matrix::operator* (Matrix m) {
    assert(_width == m._height); // matrix multiplication requires this
    int a = _height;
    int b = _width;
    int c = m._width;
    int sum;

    Matrix result(a, c);   

    for (int row = 0; row < a; row++)
        for (int col = 0; col < c; col++) {
            sum = 0;
            for (int i = 0; i < b; i++) {
                sum += _values[row][i] * _values[i][col];
            }
            result._values[row][col] = sum;
        }

    return result;
}

// prints an matrix
void Matrix::print() {
    std::cout << std::scientific << std::setprecision(2);
    for (int r=0; r < _height; r++) {
        for (int c=0; c < _width; c++) {
            std::cout << _values[r][c] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}