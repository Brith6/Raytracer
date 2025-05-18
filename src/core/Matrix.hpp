/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Matrix.hpp
*/

#pragma once

#include "Math.hpp"      // Define Vector3D, etc.
#include "Error.hpp"     // Define raytracer::Error
#include <initializer_list>
#include <iostream>
#include <vector>
#include <cmath>         // For std::fabs
#include <limits>        // For std::numeric_limits

using std::vector;
using std::string;
using std::size_t;

namespace math {
    template<typename T>
    class Matrix {
        public:
        // Constructs a matrix with the given dimensions.
        // Initializes the matrix and inverse matrix as identity matrices,
        // then computes the inverse.
        Matrix(const size_t rows, const size_t cols)
            : _rows(rows), _cols(cols) {
            createMatrix();
            createInverseMatrix();
            setInverseMatrixIdentity();
            inverse();
        }
        Matrix(const size_t rows, const size_t cols, const std::initializer_list<T>& list)
            : _rows(rows), _cols(cols)
        {
            if (list.size() != rows * cols) {
                throw raytracer::Error("Initializer list size does not match matrix dimensions.");
            }
            createMatrix();
            auto it = list.begin();
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < _cols; j++) {
                    _matrix[i][j] = *(it++);
                }
            }
            createInverseMatrix();
            setInverseMatrixIdentity();
            inverse();
        }
        // Default constructor leaves dimensions at 0.
        Matrix() : _rows(0), _cols(0) {}

        // Applies the transformation to a 3D vector, treating it as a homogeneous coordinate.
        // If "isInverse" is true, the inverse transformation is applied.
        Vector3D apply(const Vector3D &vectorToApply, const bool isInverse)
        {
            if (_matrix.empty()) {
                return vectorToApply;
            }
            // Convert to homogeneous coordinates: (x, y, z, 1)
            vector<T> tempData { vectorToApply.x,
                                 vectorToApply.y,
                                 vectorToApply.z,
                                 static_cast<T>(1.0) };

            // Create a 4x1 result matrix.
            vector<vector<T>> res = createExternalMatrix(4, 1);

            if (!isInverse) {
                for (size_t i = 0; i < 4; i++) {
                    T sum = 0;
                    for (size_t j = 0; j < 4; j++) {
                        sum += _matrix[i][j] * tempData[j];
                    }
                    res[i][0] = sum;
                }
            } else {
                // Recalculate the inverse if needed
                inverse();
                for (size_t i = 0; i < 4; i++) {
                    T sum = 0;
                    for (size_t j = 0; j < 4; j++) {
                        sum += _inverseMatrix[i][j] * tempData[j];
                    }
                    res[i][0] = sum;
                }
            }
            return Vector3D(res[0][0], res[1][0], res[2][0]);
        }

        // Provides access to the (row, col) element with bounds checking.
        T &operator()(const size_t row, const size_t col)
        {
            if (row >= _rows || col >= _cols) {
                string errorMsg = (row >= _rows)
                    ? "Row index out of bounds"
                    : "Column index out of bounds";
                throw raytracer::Error(errorMsg);
            }
            return _matrix[row][col];
        }

        // Overload for addition-assignment.
        void operator+=(const Matrix<T>& other)
        {
            checkSameSize(other);
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < _cols; j++) {
                    _matrix[i][j] += other(i, j);
                }
            }
        }

        // Overload for subtraction-assignment.
        void operator-=(const Matrix<T>& other)
        {
            checkSameSize(other);
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < _cols; j++) {
                    _matrix[i][j] -= other(i, j);
                }
            }
        }

        // Overload for multiplication-assignment (matrix multiplication).
        void operator*=(Matrix<T>& other)
        {
            if (_cols != other.getNbRows()) {
                throw raytracer::Error("Matrix multiplication size mismatch");
            }
            vector<vector<T>> res(_rows, vector<T>(other.getNbCols(), 0));
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < other.getNbCols(); j++) {
                    T sum = 0;
                    for (size_t k = 0; k < _cols; k++) {
                        sum += _matrix[i][k] * other(k, j);
                    }
                    res[i][j] = sum;
                }
            }
            _matrix = res;
        }

        // Scalar multiplication-assignment.
        void operator*=(T coef)
        {
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < _cols; j++) {
                    _matrix[i][j] *= coef;
                }
            }
        }

        // Assignment operator using the copy-swap idiom.
        Matrix<T>& operator=(Matrix<T> other)
        {
            std::swap(_rows, other._rows);
            std::swap(_cols, other._cols);
            std::swap(_matrix, other._matrix);
            std::swap(_inverseMatrix, other._inverseMatrix);
            return *this;
        }

        // Assignment from an initializer list.
        Matrix<T>& operator=(const std::initializer_list<std::initializer_list<T>>& list)
        {
            _rows = list.size();
            _cols = list.begin()->size();
            createMatrix();
            createInverseMatrix();
            setInverseMatrixIdentity();
            inverse();
            size_t i = 0;
            for (const auto& row : list) {
                size_t j = 0;
                for (const auto& value : row) {
                    _matrix[i][j] = value;
                    j++;
                }
                i++;
            }
            return *this;
        }

        size_t getNbRows() const { return _rows; }
        size_t getNbCols() const { return _cols; }

        // Debug function to print the matrix.
        void displayMatrix() const {
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < _cols; j++) {
                    std::cout << "(" << i << ", " << j << ") = " << _matrix[i][j] << "\n";
                }
            }
        }

    private:
        vector<vector<T>> _matrix;
        vector<vector<T>> _inverseMatrix;
        size_t _rows = 0;
        size_t _cols = 0;

        void checkSameSize(const Matrix<T>& other) const {
            if (_rows != other.getNbRows() || _cols != other.getNbCols()) {
                throw raytracer::Error(
                    (_rows != other.getNbRows())
                        ? "Matrix sizes differ: rows mismatch"
                        : "Matrix sizes differ: columns mismatch"
                );
            }
        }
        void createMatrix() {
            _matrix = vector<vector<T>>(_rows, vector<T>(_cols, 0));
        }
        void createInverseMatrix() {
            _inverseMatrix = vector<vector<T>>(_rows, vector<T>(_cols, 0));
        }
        void setMatrixIdentity() {
            if (_rows == _cols) {
                for (size_t i = 0; i < _rows; i++) {
                    for (size_t j = 0; j < _cols; j++) {
                        _matrix[i][j] = (i == j) ? 1 : 0;
                    }
                }
            }
        }
        void setInverseMatrixIdentity() {
            if (_rows == _cols) {
                for (size_t i = 0; i < _rows; i++) {
                    for (size_t j = 0; j < _cols; j++) {
                        _inverseMatrix[i][j] = (i == j) ? 1 : 0;
                    }
                }
            }
        }
        vector<vector<T>> createExternalMatrix(size_t rows, size_t cols) const {
            return vector<vector<T>>(rows, vector<T>(cols, 0));
        }

        // Computes the inverse of _matrix, storing the result in _inverseMatrix.
        // Uses Gaussian elimination with partial pivoting.
        void inverse()
        {
            vector<vector<T>> tmpMatrix = _matrix;  // Copy of original matrix

            for (size_t i = 0; i < _rows; i++) {
                // Find pivot row (with largest absolute value).
                size_t pivotRow = i;
                for (size_t j = i + 1; j < _rows; j++) {
                    if (std::fabs(tmpMatrix[j][i]) > std::fabs(tmpMatrix[pivotRow][i])) {
                        pivotRow = j;
                    }
                }
                //Check for singular matrix.
                // if (std::fabs(tmpMatrix[pivotRow][i]) < std::numeric_limits<T>::epsilon()) {
                //     throw raytracer::Error("Singular matrix, cannot invert");
                // }
                // Swap the current row with the pivot row (both in the temporary matrix and the inverse).
                if (pivotRow != i) {
                    std::swap(tmpMatrix[i], tmpMatrix[pivotRow]);
                    std::swap(_inverseMatrix[i], _inverseMatrix[pivotRow]);
                }
                T pivot = tmpMatrix[i][i];
                // Normalize the pivot row.
                for (size_t j = 0; j < _cols; ++j) {
                    tmpMatrix[i][j] /= pivot;
                    _inverseMatrix[i][j] /= pivot;
                }
                // Eliminate the pivot element from other rows.
                for (size_t k = 0; k < _rows; ++k) {
                    if (k != i) {
                        T factor = tmpMatrix[k][i];
                        for (size_t j = 0; j < _cols; ++j) {
                            tmpMatrix[k][j] -= factor * tmpMatrix[i][j];
                            _inverseMatrix[k][j] -= factor * _inverseMatrix[i][j];
                        }
                    }
                }
            }
        }
    }; // end of class Matrix

    template<typename T>
    Matrix<T> operator+(const Matrix<T>& one, const Matrix<T>& two)
    {
        if (one.getNbRows() != two.getNbRows() || one.getNbCols() != two.getNbCols()) {
            throw raytracer::Error("Matrix sizes differ for addition");
        }
        Matrix<T> result(one.getNbRows(), one.getNbCols());
        for (size_t i = 0; i < one.getNbRows(); i++) {
            for (size_t j = 0; j < one.getNbCols(); j++) {
                result(i, j) = one(i, j) + two(i, j);
            }
        }
        return result;
    }
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& one, const Matrix<T>& two)
    {
        if (one.getNbRows() != two.getNbRows() || one.getNbCols() != two.getNbCols()) {
            throw raytracer::Error("Matrix sizes differ for subtraction");
        }
        Matrix<T> result(one.getNbRows(), one.getNbCols());
        for (size_t i = 0; i < one.getNbRows(); i++) {
            for (size_t j = 0; j < one.getNbCols(); j++) {
                result(i, j) = one(i, j) - two(i, j);
            }
        }
        return result;
    }
    template<typename T>
    Matrix<T> operator*(const Matrix<T>& one, const Matrix<T>& two)
    {
        if (one.getNbCols() != two.getNbRows()) {
            throw raytracer::Error("Matrix multiplication size mismatch");
        }
        Matrix<T> result(one.getNbRows(), two.getNbCols());
        for (size_t i = 0; i < one.getNbRows(); i++) {
            for (size_t j = 0; j < two.getNbCols(); j++) {
                T sum = 0;
                for (size_t k = 0; k < one.getNbCols(); k++) {
                    sum += one(i, k) * two(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
    template<typename T>
    Matrix<T> operator*(T coef, const Matrix<T>& one)
    {
        Matrix<T> result(one.getNbRows(), one.getNbCols());
        for (size_t i = 0; i < one.getNbRows(); i++) {
            for (size_t j = 0; j < one.getNbCols(); j++) {
                result(i, j) = coef * one(i, j);
            }
        }
        return result;
    }
}
