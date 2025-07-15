/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Plane.cpp
*/

#include "Plane.hpp"
#include <cmath>
#include <limits>

namespace raytracer
{

double Plane::hits(const Ray &ray) const {
    math::Vector3D normal = getNormal(math::Point3D(0, 0, 0));
    
    double denominator = ray._direction.dot(normal);
    
    if (std::abs(denominator) < 1e-6) {
        return -1.0;
    }
    
    math::Point3D planePoint = getPlanePoint();
    math::Vector3D toPlane = planePoint - ray._origin;
    double distance = toPlane.dot(normal) / denominator;
    
    return (distance > 0.0) ? distance : -1.0;
}

math::Vector3D Plane::getNormal(const math::Point3D &point) const 
{
    (void)point; 
    if (_axis == "X") {
        return math::Vector3D(1.0, 0.0, 0.0);
    } else if (_axis == "Y") {
        return math::Vector3D(0.0, 1.0, 0.0);
    } else if (_axis == "Z") {
        return math::Vector3D(0.0, 0.0, 1.0);
    }
    
    return math::Vector3D(0.0, 0.0, 1.0);
}

math::Point3D Plane::getPlanePoint() const 
{
    if (_axis == "X") {
        return math::Point3D(_position, 0.0, 0.0);
    } else if (_axis == "Y") {
        return math::Point3D(0.0, _position, 0.0);
    } else if (_axis == "Z") {
        return math::Point3D(0.0, 0.0, _position);
    }
    
    return math::Point3D(0.0, 0.0, _position);
}

}