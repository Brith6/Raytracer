/*
** EPITECH PROJECT, 2024
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
using std::format;

namespace math {

    template<typename T>
    class Matrix {
    public:
        Matrix(const size_t rows, const size_t cols)
            : mRows(rows), mCols(cols) {
            createMatrice();
            createInverseMatrice();
            setMatrixInverseIndentity();
            inverse();
        };

        Matrix() : mRows(0), mCols(0) {};

        math::Vector3D apply(const math::Vector3D &vectorToApply, const bool isInverse)
        {
            if (mMatrix.empty()) {
                return vectorToApply;
            }
            vector<T> tempData {vectorToApply.mX,
                                vectorToApply.mY,
                                vectorToApply.mZ,
                                static_cast<T>(1.0)};
            vector<vector<T>> res = createMatrixExtern(4, 1);
            if (!isInverse) {
                for (size_t x = 0; x < 4; x++) {
                    T sum = 0;
                    for (size_t z = 0; z < 4; z++) {
                        sum += mMatrix[x][z] * tempData[z];
                    }
                    res[x][0] = sum;
                }
            } else {
                inverse();
                for (size_t x = 0; x < 4; x++) {
                    T sum = 0;
                    for (size_t z = 0; z < 4; z++) {
                        sum += mInverseMatrix[x][z] * tempData[z];
                    }
                    res[x][0] = sum;
                }
            }
            return (math::Vector3D(res[0][0], res[1][0], res[2][0]));
        }
        T &operator()(const size_t row, const size_t col)
        {
            if ((row >= mRows) || (col >= mCols)) {
                const string error = (row >= mRows) ?
                    format("Row bigger than size->({}/{})", row, mRows) :
                    format("Col bigger than size->({}/{})", col, mCols);
                throw raytracer::MatrixError(error);
            }
            return mMatrix[row][col];
        };
        void operator+=(Matrix<T> &other)
        {
            checkSameSize(other);
            for (size_t y = 0; y < mRows; y++) {
                for (size_t x = 0; x < mCols; x++) {
                    mMatrix[y][x] += other(y, x);
                }
            }
        };
        void operator-=(Matrix<T> &other)
        {
            checkSameSize(other);
            for (size_t y = 0; y < mRows; y++) {
                for (size_t x = 0; x < mCols; x++) {
                    mMatrix[y][x] -= other(y, x);
                }
            }
        };
        void operator*=(Matrix<T> &other)
        {
            if (mCols != other.getNbRows()) {
                throw raytracer::MatrixError("Size different for operator*=");
            }
            vector<vector<T>> res(mRows, vector<T>(other.getNbCols(), 0));
            for (size_t x = 0; x < mRows; x++) {
                for (size_t y = 0; y < other.getNbCols(); y++) {
                    T sum = 0;
                    for (size_t z = 0; z < mCols; z++) {
                        sum += mMatrix[x][z] * other(z, y);
                    }
                    res[x][y] = sum;
                }
            }
            mMatrix = res;
        };
        void operator*=(T coef)
        {
            for (size_t y = 0; y < mRows; y++) {
                for (size_t x = 0; x < mCols; x++) {
                    mMatrix[y][x] *= coef;
                }
            }
        };
        Matrix<T> &operator=(Matrix<T> other)
        {
            std::swap(mRows, other.mRows);
            std::swap(mCols, other.mCols);
            std::swap(mMatrix, other.mMatrix);
            std::swap(mInverseMatrix, other.mInverseMatrix);
            return *this;
        };
        Matrix<T> &operator=(const initializer_list<initializer_list<T>> &list)
        {
            if ((mRows == 0) && (mCols == 0)) {
                mRows = list.size();
                mCols = list.begin()->size();
                createMatrice();
                createInverseMatrice();
                setMatrixInverseIndentity();
                inverse();
            }
            size_t y = 0;
            for (auto &elem : list) {
                size_t x = 0;
                for (auto &elem2 : elem) {
                    mMatrix[y][x] = elem2;
                    x++;
                }
                y++;
            }
            return *this;
        };
        size_t getNbRows() const { return mRows; };
        size_t getNbCols() const { return mCols; };
        void displayMatrix()
        {
            for (size_t i = 0; i < mRows; i++) {
                for (size_t j = 0; j < mCols; j++) {
                    std::cout << "(" << i << ", " << j << ") = "
                    << mMatrix[i][j] << "\n";
                }
            }
        }

    private:
        vector<vector<T>> mMatrix = vector<vector<T>>();
        vector<vector<T>> mInverseMatrix = vector<vector<T>>();
        size_t mRows;
        size_t mCols;

        void checkSameSize(const Matrix<T> &other) const
        {
            if ((mRows != other.getNbRows()) || (mCols != other.getNbCols())) {
                throw MatrixError(mRows != other.getNbRows() ?
                "Sizes are different (rows differents)":
                "Sizes are different (cols differents)");
            }
        };
        void createMatrice()
        {
            mMatrix = vector<vector<T>>(mRows, vector<T>(mCols, 0));
        }
        void createInverseMatrice()
        {
            mInverseMatrix = vector<vector<T>>(mRows, vector<T>(mCols, 0));
        }
        void setMatrixIdentity() {
            if (mRows == mCols) {
                for (size_t i = 0; i < mRows; i++) {
                    for (size_t j = 0; j < mCols; j++) {
                        mMatrix[i][j] = 1;
                    }
                }
            }
        }
        void setMatrixInverseIndentity() {
            if (mRows == mCols) {
                for (size_t i = 0; i < mRows; i++) {
                    for (size_t j = 0; j < mCols; j++) {
                        mInverseMatrix[i][j] = 1;
                    }
                }
            }
        }
        vector<vector<T>> createMatrixExtern(size_t rows, size_t cols)
        {
            return vector<vector<T>>(rows, vector<T>(cols, 0));
        }
        void inverse()
        {
            vector<vector<T>> tmpMatrix = mMatrix;
            for (size_t i = 0; i < mRows; i++) {
                size_t pivotRow = i;
                for (size_t j = i + 1; j < mRows; j++) {
                    if (abs(tmpMatrix[j][i]) > abs(tmpMatrix[pivotRow][i])) {
                        pivotRow = j;
                    }
                }
                if (pivotRow != i) {
                    std::swap(tmpMatrix[i], tmpMatrix[pivotRow]);
                    std::swap(mInverseMatrix[i], mInverseMatrix[pivotRow]);
                }
                T pivot = tmpMatrix[i][i];
                for (size_t j = 0; j < mCols; ++j) {
                    tmpMatrix[i][j] /= pivot;
                    mInverseMatrix[i][j] /= pivot;
                }
                for (size_t k = 0; k < mRows; ++k) {
                    if (k != i) {
                        T factor = tmpMatrix[k][i];
                        for (size_t j = 0; j < mCols; ++j) {
                            tmpMatrix[k][j] -= factor * tmpMatrix[i][j];
                            mInverseMatrix[k][j] -= factor * mInverseMatrix[i][j];
                        }
                    }
                }
            }
        }
    };
}
