//
//  matrix.hpp
//  matrix_xcode
//
//  Created by Makar Q on 13.10.2020.
//

#pragma once

#include <vector>
#include <iostream>


namespace task {

const double EPS = 1e-6;


class OutOfBoundsException : public std::exception {
public:
    const char* what() const noexcept override {
            return "OutOfBoundsException";
        }
};

class SizeMismatchException : public std::exception {
public:
    const char* what() const noexcept override {
            return "SizeMismatchException";
        }
};
class MatrixProxy;

class Matrix {
    size_t rows_, cols_;
    double** matrix_;
    
    friend class MatrixProxy;
public:

    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& copy);
    Matrix& operator=(const Matrix& a);
    Matrix(const Matrix& copy, size_t col);
    ~Matrix();

    double& get(size_t row, size_t col);
    const double& get(size_t row, size_t col) const;
    void set(size_t row, size_t col, const double& value);
    void resize(size_t new_rows, size_t new_cols);

    MatrixProxy operator[](size_t row);
    const MatrixProxy operator[](size_t row) const;

    Matrix& operator+=(const Matrix& a);
    Matrix& operator-=(const Matrix& a);
    Matrix& operator*=(const Matrix& a);
    Matrix& operator*=(const double& number);

    Matrix operator+(const Matrix& a) const;
    Matrix operator-(const Matrix& a) const;
    Matrix operator*(const Matrix& a) const;
    Matrix operator*(const double& a) const;

    Matrix operator-() const;
    Matrix operator+() const;

    double det() const;
    void transpose();
    Matrix transposed() const;
    double trace() const;

    std::vector<double> getRow(size_t row);
    std::vector<double> getColumn(size_t column);

    bool operator==(const Matrix& a) const;
    bool operator!=(const Matrix& a) const;
    
    size_t getRows() const;
    size_t getCols() const;

};

class MatrixProxy{
    size_t cols_;
    double* row_;
    
public:
    MatrixProxy(Matrix* m, size_t row_idx);
    MatrixProxy(const Matrix* m, size_t row_idx);
    
    double& operator [] (size_t col_idx);
    const double operator [] (size_t col_idx) const;
    
};


Matrix operator*(const double& a, const Matrix& b);

std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
std::istream& operator>>(std::istream& input, Matrix& matrix);



}  // namespace task
