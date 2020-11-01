//
//  matrix.cpp
//  matrix_xcode
//
//  Created by Makar Q on 13.10.2020.
//

#include "matrix.h"


using namespace task;

Matrix::Matrix() {
    rows_ = 1;
    cols_ = 1;
    matrix_ = new double *[rows_];
    matrix_[0] = new double [cols_];
    matrix_[0][0] = 1;
}

Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols){
    matrix_ = new double *[rows_];
    for (size_t i = 0; i < rows_; i++){
        matrix_[i] = new double [cols_];
        for (size_t j = 0; j < cols_; j++) {
            if (i == j) {
                matrix_[i][j] = 1;
            }
            else {
                matrix_[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix(const Matrix& copy) {
    rows_ = copy.rows_;
    cols_ = copy.cols_;
    
    matrix_ = new double *[rows_];
    for (size_t i = 0; i < rows_; i++){
        matrix_[i] = new double [cols_];
        for (size_t j = 0; j < cols_; j++) {
            matrix_[i][j] = copy[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& copy, size_t col) {
    rows_ = copy.rows_ - 1;
    cols_ = copy.cols_ - 1;
    
    matrix_ = new double *[rows_];
    for (size_t i = 0; i < rows_; i++){
        matrix_[i] = new double [cols_];
    }
    for (size_t i = 1; i < copy.rows_; i++){
        size_t k = 0;
        for (size_t j = 0; j < copy.cols_; j++) {
            if (j != col) {
                matrix_[i - 1][k++] = copy[i][j];
            }
            
        }
    }
}

Matrix::~Matrix() {
    for (size_t i = 0; i < rows_; i++){
        delete [] matrix_[i];
    }
    delete [] matrix_;
}

Matrix& Matrix::operator=(const Matrix& a) {
    Matrix tmp(a);
    for (size_t i = 0; i < rows_; i++){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    
    rows_ = tmp.rows_;
    cols_ = tmp.cols_;
    
    matrix_ = new double *[rows_];
    for (size_t i = 0; i < rows_; i++){
        matrix_[i] = new double [cols_];
        for (size_t j = 0; j < cols_; j++) {
            matrix_[i][j] = tmp[i][j];
        }
    }
    
    return *this;
}


double& Matrix::get(size_t row, size_t col) {
    if (row >= rows_ || col >= cols_) {
        throw OutOfBoundsException();
    }
    else {
        return matrix_[row][col];
    }
}

const double& Matrix::get(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw OutOfBoundsException();
    }
    else {
        return matrix_[row][col];
    }
}

void Matrix::set(size_t row, size_t col, const double& value) {
    if (row >= rows_ || col >= cols_) {
        throw OutOfBoundsException();
    }
    else {
        matrix_[row][col] = value;
    }
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
    size_t min_rows = std::min(new_rows, rows_);
    size_t min_cols = std::min(new_cols, cols_);
    
    double** tmp;
    tmp = new double *[new_rows];
    for (size_t i = 0; i < min_rows; i++){
        tmp[i] = new double [new_cols];
        for (size_t j = 0; j < min_cols; j++) {
            tmp[i][j] = matrix_[i][j];
        }
        for (size_t j = min_cols; j < new_cols; j++) {
            tmp[i][j] = 0;
        }
    }
    for (size_t i = min_rows; i < new_rows; i++){
        tmp[i] = new double [new_cols];
        for (size_t j = 0; j < new_cols; j++) {
            tmp[i][j] = 0;
        }
    }
    
    for (size_t i = 0; i < rows_; i++){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    
    rows_ = new_rows;
    cols_ = new_cols;
    matrix_ = tmp;
    
}

MatrixProxy Matrix::operator [] (size_t row_idx) {
    if (row_idx >= rows_) {
        throw OutOfBoundsException();
    }
    return MatrixProxy(this, row_idx);
}

const MatrixProxy Matrix::operator [] (size_t row_idx) const {
    if (row_idx >= rows_) {
        throw OutOfBoundsException();
    }
    return MatrixProxy(this, row_idx);
}


Matrix& Matrix::operator+=(const Matrix& a) {
    if (rows_ != a.rows_ || cols_ != a.cols_ ) {
        throw SizeMismatchException();
    }
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            matrix_[i][j] += a[i][j];
        }
    }
    
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& a) {
    if (rows_ != a.rows_ || cols_ != a.cols_ ) {
        throw SizeMismatchException();
    }
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            matrix_[i][j] -= a[i][j];
        }
    }
    
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& a) {
    if (cols_ != a.rows_ ) {
        throw SizeMismatchException();
    }
    
    double** c = new double *[rows_];
    for (size_t i = 0; i < rows_; i++) {
        c[i] = new double [a.cols_];
        for (size_t j = 0; j < a.cols_; j++) {
            c[i][j] = 0;
            for (size_t k = 0; k < cols_; k++) {
                c[i][j] += matrix_[i][k] * a.matrix_[k][j];
            }
        }
    }
    
    for (size_t i = 0; i < rows_; i++){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    
    cols_ = a.cols_;
    matrix_ = c;
    
    return *this;
}

Matrix& Matrix::operator*=(const double& number) {
    for (size_t i = 0; i < rows_; i++){
        for (size_t j = 0; j < cols_; j++) {
            matrix_[i][j] *= number;
        }
    }
    
    return *this;
}

Matrix Matrix::operator+(const Matrix& a) const {
    if (rows_ != a.rows_ || cols_ != a.cols_ ) {
        throw SizeMismatchException();
    }
    
    Matrix tmp(*this);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            tmp.matrix_[i][j] += a[i][j];
        }
    }
    
    return tmp;
}

Matrix Matrix::operator-(const Matrix& a) const {
    if (rows_ != a.rows_ || cols_ != a.cols_ ) {
        throw SizeMismatchException();
    }
    Matrix tmp(*this);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            tmp.matrix_[i][j] -= a[i][j];
        }
    }
    
    return tmp;
}

Matrix Matrix::operator*(const Matrix& a) const {
    if (cols_ != a.rows_ ) {
        throw SizeMismatchException();
    }
    
    Matrix tmp(rows_, a.cols_);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < a.cols_; j++) {
            tmp.matrix_[i][j] = 0;
            for (size_t k = 0; k < cols_; k++) {
                tmp.matrix_[i][j] += matrix_[i][k] * a.matrix_[k][j];
            }
        }
    }
    
    return tmp;
}

Matrix Matrix::operator*(const double& number) const {
    Matrix tmp(*this);
    for (size_t i = 0; i < rows_; i++){
        for (size_t j = 0; j < cols_; j++) {
            tmp.matrix_[i][j] *= number;
        }
    }
    
    return tmp;
}

Matrix Matrix::operator-() const {
    Matrix tmp(*this);
    for (size_t i = 0; i < rows_; i++){
        for (size_t j = 0; j < cols_; j++) {
            tmp.matrix_[i][j] = -tmp.matrix_[i][j];
        }
    }
    
    return tmp;
}

Matrix Matrix::operator+() const {
    return Matrix(*this);
}


double Matrix::det() const {
    if (cols_ != rows_ ) {
        throw SizeMismatchException();
    }
    
    if (rows_ == 1) {
        return matrix_[0][0];
    }
    
    double determinant = 0;
    int sign = 1;
    for (size_t j = 0; j < cols_; j++) {
        Matrix tmp(*this, j);
        // std::cout << tmp << "\n\n";
        determinant += sign * matrix_[0][j] * tmp.det();
        sign *= -1;
    }
    
    return determinant;
}

void Matrix::transpose() {
    double** c = new double *[cols_];
    for (size_t i = 0; i < cols_; i++) {
        c[i] = new double [rows_];
        for (size_t j = 0; j < rows_; j++) {
            c[i][j] = matrix_[j][i];
            
        }
    }
    
    for (size_t i = 0; i < rows_; i++){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    
    matrix_ = c;
    size_t a = cols_;
    cols_ = rows_;
    rows_ = a;
}

Matrix Matrix::transposed() const {
    Matrix tmp(cols_, rows_);
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            tmp.matrix_[j][i] = matrix_[i][j];
        }
    }
    return tmp;
}

double Matrix::trace() const {
    if (cols_ != rows_) {
        throw SizeMismatchException();
    }
    double sum = 0;
    for (size_t i = 0; i < rows_; i++) {
        sum += matrix_[i][i];
    }
    return sum;
}

std::vector<double> Matrix::getRow(size_t row) {
    if (row >= rows_) {
        throw OutOfBoundsException();
    }
    std::vector<double> vec;
    for (size_t j = 0; j < cols_; j++) {
        vec.push_back(matrix_[row][j]);
    }
    return vec;
}

std::vector<double> Matrix::getColumn(size_t column) {
    if (column >= cols_) {
        throw OutOfBoundsException();
    }
    std::vector<double> vec;
    for (size_t i = 0; i < rows_; i++) {
        vec.push_back(matrix_[i][column]);
    }
    return vec;
}



bool Matrix::operator==(const Matrix& a) const {
    if (rows_ != a.rows_ || cols_ != a.cols_ ) {
        throw SizeMismatchException();
    }
    
    for (size_t i = 0; i < rows_; i++){
        for (size_t j = 0; j < cols_; j++) {
            if (fabs(matrix_[i][j] - a.matrix_[i][j]) > EPS) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& a) const {
    return !(*this == a);
}

size_t Matrix::getRows() const {
    return rows_;
}

size_t Matrix::getCols() const {
    return cols_;
}







MatrixProxy::MatrixProxy(Matrix* m, size_t row_idx) {
    row_ = m->matrix_[row_idx];
    cols_ = m->cols_;
}

MatrixProxy::MatrixProxy(const Matrix* m, size_t row_idx) {
    row_ = m->matrix_[row_idx];
    cols_ = m->cols_;
}

double& MatrixProxy::operator [] (size_t col_idx) {
    if (col_idx >= cols_) {
        throw OutOfBoundsException();
    }
    return row_[col_idx];
}

const double MatrixProxy::operator [] (size_t col_idx) const {
    if (col_idx >= cols_) {
        throw OutOfBoundsException();
    }
    return row_[col_idx];
}







Matrix task::operator*(const double& a, const Matrix& b) {
    Matrix tmp(b);
    tmp *= a;
    
    return tmp;
}

std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.getRows(); i++) {
        for (size_t j = 0; j < matrix.getCols(); j++) {
            output << matrix[i][j] << " ";
        }
        output << "\n";
    }
    return output;
}

std::istream& task::operator>>(std::istream& input, Matrix& matrix) {
    int row, col;
    double value;
    input >> row >> col;
    matrix = Matrix(row, col);
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            input >> value;
            matrix.set(i, j, value);
        }
    }
    return input;
}
