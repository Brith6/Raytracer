/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Matrix.hpp
*/

#pragma once

#include "Math.hpp"
#include "../error/Error.hpp"
#include <initializer_list>
#include <iostream>
#include <vector>
#include <format>

using std::cout;
using std::initializer_list;
using std::size_t;
using std::string;
using std::vector;

namespace math {

    template<typename T>
    class Matrix {
    public:
        Matrix() : _rows(0), _cols(0) {};
        Matrix(const size_t rows, const size_t cols)
            : _rows(rows), _cols(cols), mMatrix(rows, vector<T>(cols, T{})) {}

        T &operator()(const size_t row, const size_t col)
        {
            if (row >= _rows || col >= _cols)
                throw std::out_of_range("Matrix index out of range.");
            return mMatrix[row][col];
        };
        Matrix<T>& operator+=(const Matrix<T> &other) {
            checkSameSize(other);
            for (size_t y = 0; y < _rows; y++) {
                for (size_t x = 0; x < _cols; x++)
                    mMatrix[y][x] += other(y, x);
            }
            return *this;
        }
        Matrix<T>& operator-=(const Matrix<T> &other) {
            checkSameSize(other);
            for (size_t y = 0; y < _rows; y++) {
                for (size_t x = 0; x < _cols; x++)
                    mMatrix[y][x] -= other(y, x);
            }
            return *this;
        }
        Matrix<T>& operator*=(const Matrix<T> &other) {
            if (_cols != other.getNbRows())
                throw raytracer::MatrixError("Size different for operator*=");
            vector<vector<T>> result(_rows, vector<T>(other.getNbCols(), T{}));
            for (size_t i = 0; i < _rows; i++) {
                for (size_t j = 0; j < other.getNbCols(); j++) {
                    T sum = T{};
                    for (size_t k = 0; k < _cols; k++)
                        sum += mMatrix[i][k] * other(k, j);
                    result[i][j] = sum;
                }
            }
            mMatrix = std::move(result);
            _cols = other.getNbCols();
            return *this;
        }
        Matrix<T>& operator*=(const T& scalar) {
            for (std::size_t y = 0; y < _rows; y++) {
                for (std::size_t x = 0; x < _cols; x++)
                    mMatrix[y][x] *= scalar;
            }
            return *this;
        }
        Matrix<T>& operator=(Matrix<T> other) {
            std::swap(_rows, other._rows);
            std::swap(_cols, other._cols);
            std::swap(mMatrix, other.mMatrix);
            return *this;
        }
        Matrix<T>& operator=(const std::initializer_list<std::initializer_list<T>> &list) {
            _rows = list.size();
            _cols = (_rows > 0) ? list.begin()->size() : 0;
            mMatrix.assign(_rows, std::vector<T>(_cols));

            std::size_t y = 0;
            for (const auto &row_list : list) {
                if (row_list.size() != _cols)
                    throw raytracer::MatrixError("All rows in initializer_list must have the same size.");
                std::copy(row_list.begin(), row_list.end(), mMatrix[y].begin());
                y++;
            }
            return *this;
        }
        size_t getNbRows() const { return _rows; };
        size_t getNbCols() const { return _cols; };

    private:
        vector<vector<T>> mMatrix = vector<vector<T>>();
        size_t _rows;
        size_t _cols;

        void checkSameSize(const Matrix<T> &other) const
        {
            if ((_rows != other.getNbRows()) || (_cols != other.getNbCols()))
                throw std::out_of_range("Matrix index out of range.");
        }
        void setMatrixIdentity() {
            if (_rows != _cols)
                 throw std::logic_error("Identity matrix must be square.");
            for (std::size_t i = 0; i < _rows; i++) {
                for (std::size_t j = 0; j < _cols; j++)
                    mMatrix[i][j] = (i == j) ? T{1} : T{0};
            }
        }
    };
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        os << "Matrix(" << m.getNbRows() << "x" << m.getNbCols() << ") [\n";
        for (std::size_t i = 0; i < m.getNbRows(); ++i) {
            os << "  ";
            for (std::size_t j = 0; j < m.getNbCols(); ++j) {
                os << m(i, j) << (j == m.getNbCols() - 1 ? "" : ", ");
            }
            os << "\n";
        }
        os << "]";
        return os;
    }
}
