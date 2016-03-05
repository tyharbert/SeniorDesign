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

// constructor for A matrix
Matrix::Matrix(Corners orig, Corners dest): Matrix(8) {
    int* ox = orig.xArray();
    int* oy = orig.yArray();
    int* dx = dest.xArray();
    int* dy = dest.yArray();
    int row;

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

// constructor for B matrix
Matrix::Matrix(Corners dest): Matrix(8, 1) {
    int* dx = dest.xArray();
    int* dy = dest.yArray();

    for (int i=0; i < 4; i++) {
        _values[i][0] = dx[i];
    }

    for (int i=0; i < 4; i++) {
        _values[i+4][0] = dy[i];
    }
}

// constructor for P matrix
Matrix::Matrix(int* piv, int n): Matrix(n+1) {
    int col;

    for (int row = 0; row < n; row++) {
        col = piv[row];
        // if the column was previously set
        // change col to the last row it was
        // set on
        for (int i = row-1; i >= 0; i--) {
            if (_values[i][col] == 1) {
                col = i;
                break;
            }
        }
        _values[row][col] = 1;
    }

    // find the coulmn without a 1 in the last row
    bool found1 = false;
    for (int c = 0; c < _width; c++) {
        found1 = false;
        for (int r = 0; r < n; r++) {
            if (_values[r][c] == 1) {
                found1 = true;
                break;
            }
        }
        if (!found1) {
            _values[n][c] = 1;
            break;
        }
    }
}

// matrix destructor
Matrix::~Matrix() {
    deallocate_values();
}

// computes the LU decomposition
// of an NxN matrix
Matrix Matrix::lu(bool up) {
    assert(_height == _width); // must be a square matrix
    int n = _height - 1;
    int mu;

    int* p = new int[n](); // contains pivot values
    for (int i = 0; i < n; i++)
        p[i] = -1;

    // partial pivot gaussian elimination
    for (int k = 0; k < n; k++) {
        mu = inf_norm(Range(k, n),k);
        row_swap(k, mu, Range((up?k:0), n));
        p[k] = mu;

        if (_values[k][k] != 0) {
            gauss(Range(k+1, n), k);
            gauss_app(Range(k+1, n), Range(k+1, n));
        }
    }

    // set upper or lower values to 0
    for (int i = 0; i < n; i++)
        for (int j = i+1; j <= n; j++)
            _values[(up?j:i)][(up?i:j)] = 0;

    // set diagonal to 1 for lower matrix
    if (!up)
        for (int i = 0; i <= n; i++)
            _values[i][i] = 1;

    return Matrix(p, n);
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

// deallocates the float** of values
void Matrix::deallocate_values() {
    for (int i=0; i < _height; i++)
        delete _values[i];
    delete _values;
}

// preforms forward substitiution
Matrix Matrix::forward_sub(const Matrix& m) { 
    assert(m._width == 1 && _height == m._height);
    float temp;

    Matrix result(_height, 1);

    for (int r = 0; r < _height; r++) {
        temp = m._values[r][0];
        for (int n = 0; n < r; n++)
            temp -= _values[r][n]*result._values[n][0];
        result._values[r][0] = temp / _values[r][r];
    }

    return result;
}

// preforms forward substitiution
Matrix Matrix::back_sub(const Matrix& m) { 
    assert(m._width == 1 && _height == m._height);
    float temp;

    Matrix result(_height, 1);

    for (int r = _height-1; r >= 0; r--) {
        temp = m._values[r][0];
        for (int n = _height-1; n > r; n--)
            temp -= _values[r][n]*result._values[n][0];
        result._values[r][0] = temp / _values[r][r];
    }

    return result;
}

void Matrix::reshape(int height, int width, int defaults) {
    assert(_height*_width <= height*width); // can only reshape into larger or equal
    int size = height*width;
    int row = -1;
    int _size = _height*_width;
    int _row = -1;

    float** temp = new float*[height];
    for (int i=0; i < height; i++)
        temp[i] = new float[width];

    for (int i = 0; i < size; i++) {
        if (i%width == 0) row++;
        if (i%_width == 0) _row++;

        if (i < _size)
            temp[row][i%width] = _values[_row][i%_width];
        else
            temp[row][i%width] = defaults;
    }

    deallocate_values();

    _height = height;
    _width = width;
    _values = temp;
}

// multiplies two matricies
// axb * bxc = axc
Matrix Matrix::operator* (const Matrix& m) {
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
                sum += _values[row][i] * m._values[i][col];
            }
            result._values[row][col] = sum;
        }

    return result;
}

// prints an matrix
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << std::scientific << std::setprecision(2);
    for (int r=0; r < m._height; r++) {
        for (int c=0; c < m._width; c++) {
            os << m._values[r][c] << '\t';
        }
        os << std::endl;
    }

    return os;
}