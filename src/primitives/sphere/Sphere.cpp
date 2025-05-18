/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"

bool raytracer::Sphere::hits(const Ray &r, HitData& data) const
{
    const math::Vector3D oc = r._origin - _bcenter;
    const double a = r._direction.dot(r._direction);
    const double b = 2.0 * oc.dot(r._direction);
    const double c = oc.dot(oc) - _bradius * _bradius;
    const double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return false;
    data.t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    return true;
}

math::Vector3D raytracer::Sphere::getNormal(const math::Point3D &point) const
{
    math::Vector3D normal = point - _bcenter;

    normal.normalize();
    return normal;
}