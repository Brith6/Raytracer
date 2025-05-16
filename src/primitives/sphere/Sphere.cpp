/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"

bool raytracer::Sphere::hits(const Ray &r, HitData& data) const
{
    const math::Vector3D oc = r._origin - _center;
    float a = r._direction.dot(r._direction);
    float b = 2.0 * oc.dot(r._direction);
    float c = oc.dot(oc) - _radius * _radius;
    const double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return false;
    data.t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    data.p = r.at(data.t);
    data.normal = getNormal(data.p);
    return true;
}

math::Vector3D raytracer::Sphere::getNormal(const math::Point3D &point) const
{
    math::Vector3D normal = point - _center;

    normal.normalize();
    return normal;
}