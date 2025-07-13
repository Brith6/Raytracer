/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Plane.cpp
*/

#include "Plane.hpp"
<<<<<<< HEAD
#include <cmath>
#include <limits>


using std::abs;

    double raytracer::Plane::hits(const Ray &ray) const
    {
        double t;
        double denominator;

        if (_axis == "X") {
            denominator = ray._direction.x;
            if (std::abs(denominator) < 1e-6)
                return -1.0;
            t = (_position - ray._origin.x) / denominator;
        } else if (_axis == "Y") {
            denominator = ray._direction.y;
            if (std::abs(denominator) < 1e-6)
                return -1.0;
            t = (_position - ray._origin.y) / denominator;
        } else if (_axis == "Z") {
            denominator = ray._direction.z;
            if (std::abs(denominator) < 1e-6)
                return -1.0;
            t = (_position - ray._origin.z) / denominator;
        } else {
            return -1.0;
        }

        if (t > 0)
            return t;
        return -1.0;
    }

math::Vector3D raytracer::Plane::getNormal(const math::Point3D &point) const
{
    (void)point;
    if (_axis == "X") {
        return math::Vector3D(1.0, 0.0, 0.0);
    }
    if (_axis == "Y") {
        return math::Vector3D(0.0, 0.0, 1.0);
    }
    if (_axis == "Z") {
        return math::Vector3D(0.0, 1.0, 0.0);
    }
    return math::Vector3D(0.0, 0.0, 0.0);
}
>>>>>>> c846fb481342ca8fdcc7569d126d2eb2e727c8b8
