/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

bool raytracer::Plane::hits(const Ray &ray, HitData& hitData) const

{
    math::Point3D position;

    if (_axis == "X")
        position = math::Point3D(_position, 0.0, 0.0);
    else if (_axis == "Y")
        position = math::Point3D(0.0, 0.0, _position);
    else if (_axis == "Z")
        position = math::Point3D(0.0, _position, 0.0);
    else
        return false;
    return checkRayPlaneIntersection(ray, position, hitData);
}

bool raytracer::Plane::checkRayPlaneIntersection(
    const Ray &ray, const math::Point3D &position, HitData& hitData) const
{
    const math::Vector3D normal = getNormal(position);
    const double epsilon = 1e-10;
    const double rayPlaneAngle = ray._direction.dot(normal);
    const math::Vector3D pointOnPlane = position - ray._origin;
    const double t = pointOnPlane.dot(normal) / rayPlaneAngle;

    if (abs(rayPlaneAngle) < epsilon)
        return false;
    hitData.t = t;
    hitData.p = ray._origin;
    hitData.normal = getNormal(hitData.p);
    return true;
}

math::Vector3D raytracer::Plane::getNormal(const math::Point3D &point) const
{
    (void)point;
    if (_axis == "X")
        return math::Vector3D(1.0, 0.0, 0.0);
    if (_axis == "Y")
        return math::Vector3D(0.0, 0.0, 1.0);
    if (_axis == "Z")
        return math::Vector3D(0.0, 1.0, 0.0);
    return math::Vector3D(0.0, 0.0, 0.0);
}