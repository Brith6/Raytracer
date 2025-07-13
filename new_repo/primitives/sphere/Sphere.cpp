/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"
#include <cmath>
#include <stdexcept>



double raytracer::Sphere::hits(const Ray &ray) const
{
        math::Vector3D oc = ray._origin - _center;
        double a = ray._direction.dot(ray._direction);
        double b = 2.0 * ray._direction.dot(oc);
        double c = oc.dot(oc) - _radius * _radius;

        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return -1.0;

        double t = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (t > 0) {
        return t;
        }

    t = (-b + std::sqrt(discriminant)) / (2.0 * a);
    if (t > 0) {
        return t;
    }
    return -1.0;
}

math::Vector3D raytracer::Sphere::getNormal(const math::Point3D &point) const
{
    math::Vector3D normal = point - _center;

    normal.normalize();
    return normal;
}