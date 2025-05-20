/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"

using std::numeric_limits;

raytracer::Color raytracer::PointLight::getColorShadow(
    const math::Point3D &intersectionPoint,
    const math::Vector3D &normal,
    const vector<unique_ptr<IPrimitive>> &primitives)
{
    World world;
    const math::Vector3D lightDir = (mBaseOrigin - intersectionPoint);
    const Ray shadowRay(
        intersectionPoint + (normal * 0.01),
        math::Vector3D::normalize(lightDir)
    );
    const double closestHit = world.hit(shadowRay, primitives);

    if (closestHit < lightDir.length()) {
        return Color(0.0, 0.0, 0.0);
    }
    return mBaseColor * world.getDistance(
        mBaseOrigin, intersectionPoint
    );
}
