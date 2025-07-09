/*
** EPITECH PROJECT, 2025
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
            Vector3D(const double x, const double y, const double z)
                : x(x), y(y), z(z) {}
            double length() const {
                return sqrt((x * x) + (y * y) + (z * z));
            }
            double dot(const Vector3D& other) const {
                return (x * other.x) + (y * other.y) + (z * other.z);
            }
            Vector3D cross(const Vector3D& other) const {
                return Vector3D(
                    (y * other.z) - (z * other.y),
                    (z * other.x) - (x * other.z),
                    (x * other.y) - (y * other.x)
                );
            }
            Vector3D operator+(const Vector3D& other) const {
                return Vector3D(x + other.x, y + other.y, z + other.z);
            }
            Vector3D operator+=(const Vector3D& other) {
                x += other.x;
                y += other.y;
                z += other.z;
                return *this;
            }
            Vector3D operator-(const Vector3D& other) const {
                return Vector3D(x - other.x, y - other.y, z - other.z);
            }
            Vector3D operator-=(const Vector3D& other) {
                x -= other.x;
                y -= other.y;
                z -= other.z;
                return *this;
            }
            Vector3D operator*(const double scalar) const {
                return Vector3D(x * scalar, y * scalar, z * scalar);
            }
            Vector3D operator*(const Vector3D& other) const {
                return Vector3D(x * other.x, y * other.y, z * other.z);
            }
            Vector3D operator*=(const Vector3D& other) {
                x *= other.x;
                y *= other.y;
                z *= other.z;
                return *this;
            }
            Vector3D operator*=(const double scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
                return *this;
            }
            Vector3D operator/(const Vector3D& other) const {
                return Vector3D(x / other.x, y / other.y, z / other.z);
            }
            Vector3D operator/(const double scalar) const {
                return Vector3D(x / scalar, y / scalar, z / scalar);
            }
            Vector3D operator/=(const Vector3D& other) {
                x /= other.x;
                y /= other.y;
                z /= other.z;
                return *this;
            }
            Vector3D operator/=(const double scalar) {
                x /= scalar;
                y /= scalar;
                z /= scalar;
                return *this;
            }
            Vector3D operator-() const {
                return Vector3D(-x, -y, -z);
            }
            void normalize() {
                const double len = length();
                if (len > 0)
                    *this /= len;
            }
            static Vector3D normalized(const Vector3D &vector) {
                Vector3D result = vector;
                result.normalize();
                return result;
            }
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;
    };
    class Point3D {
        public:
            Point3D() = default;
            Point3D(const double x, const double y, const double z)
                : x(x), y(y), z(z) {}
            Point3D operator+(const Point3D& other) const {
                return Point3D(x + other.x, y + other.y, z + other.z);
            }
            Point3D operator+(const Vector3D& vec) const {
                return Point3D(x + vec.x, y + vec.y, z + vec.z);
            }
            Point3D operator+=(const Vector3D& vec) {
                x += vec.x;
                y += vec.y;
                z += vec.z;
                return *this;
            }
            Point3D operator-(const Vector3D& other) const {
                return Point3D(x - other.x, y - other.y, z - other.z);
            }
            Vector3D operator-(const Point3D &p) const {
                return Vector3D(x - p.x, y - p.y, z - p.z);
            }
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;
    };
}