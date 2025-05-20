/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Math.hpp
*/

#pragma once
#include <iostream>
#include <cmath>

namespace math {
    class Vector3D {
        public:
            Vector3D() = default;
            Vector3D(const double ex, const double ey, const double ez)
                : mX(ex), mY(ey), mZ(ez) {}
            ~Vector3D() = default;
            double length() const {
                return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
            }
            double dot(const Vector3D& other) const {
                return (mX * other.mX) + (mY * other.mY) + (mZ * other.mZ);
            }
            Vector3D operator+(const Vector3D& other) const {
                return Vector3D(mX + other.mX, mY + other.mY, mZ + other.mZ);
            }
            Vector3D operator+=(const Vector3D& other) {
                mX += other.mX;
                mY += other.mY;
                mZ += other.mZ;
                return *this;
            }
            Vector3D operator-(const Vector3D& other) const {
                return Vector3D(mX - other.mX, mY - other.mY, mZ - other.mZ);
            }
            Vector3D operator-=(const Vector3D& other) {
                mX -= other.mX;
                mY -= other.mY;
                mZ -= other.mZ;
                return *this;
            }
            Vector3D operator*(const double scalar) const {
                return Vector3D(mX * scalar, mY * scalar, mZ * scalar);
            }
            Vector3D operator*(const Vector3D& other) const {
                return Vector3D(mX * other.mX, mY * other.mY, mZ * other.mZ);
            }
            Vector3D operator*=(const Vector3D& other) {
                mX *= other.mX;
                mY *= other.mY;
                mZ *= other.mZ;
                return *this;
            }
            Vector3D operator*=(const double scalar) {
                mX *= scalar;
                mY *= scalar;
                mZ *= scalar;
                return *this;
            }
            Vector3D operator/(const Vector3D& other) const {
                return Vector3D(mX / other.mX, mY / other.mY, mZ / other.mZ);
            }
            Vector3D operator/(const double scalar) const {
                return Vector3D(mX / scalar, mY / scalar, mZ / scalar);
            }
            Vector3D operator/=(const Vector3D& other) {
                mX /= other.mX;
                mY /= other.mY;
                mZ /= other.mZ;
                return *this;
            }
            Vector3D operator/=(const double scalar) {
                mX /= scalar;
                mY /= scalar;
                mZ /= scalar;
                return *this;
            }
            Vector3D operator-() const {
                return Vector3D(-mX, -mY, -mZ);
            }
            void normalize() {
                const double len = length();
                
                mX /= len;
                mY /= len;
                mZ /= len;
            }
            static Vector3D normalize(const Vector3D &vector) {
                const double len = vector.length();
                return Vector3D(vector.mX / len, vector.mY / len, vector.mZ / len);
            }
            double mX = 0;
            double mY = 0;
            double mZ = 0;
    };
    class Point3D {
        public:
            Point3D() = default;
            Point3D(const double ex, const double ey, const double ez)
                : mX(ex), mY(ey), mZ(ez) {}
            ~Point3D() = default;
            Point3D operator+(const Point3D& other) const {
                return Point3D(mX + other.mX, mY + other.mY, mZ + other.mZ);
            }
            Point3D operator+(const Vector3D& vec) const {
                return Point3D(mX + vec.mX, mY + vec.mY, mZ + vec.mZ);
            }
            Point3D operator+=(const Vector3D& vec) {
                mX += vec.mX;
                mY += vec.mY;
                mZ += vec.mZ;
                return *this;
            }
            Point3D operator-(const Vector3D& other) const {
                return Point3D(mX - other.mX, mY - other.mY, mZ - other.mZ);
            }
            Vector3D operator-(const Point3D &p) const {
                return Vector3D(mX - p.mX, mY - p.mY, mZ - p.mZ);
            }
            double mX = 0.0;
            double mY = 0.0;
            double mZ = 0.0;
    };
}