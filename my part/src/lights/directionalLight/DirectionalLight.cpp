/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"

using std::numeric_limits;

raytracer::Color raytracer::DirectionalLight::getColorShadow(
    const math::Point3D &intersectionPoint,
    const math::Vector3D &normal,
    const vector<unique_ptr<IPrimitive>> &primitives)
{
    World world;
    const math::Vector3D lightDir = math::Vector3D::normalize(mBaseDirection);
    const Ray shadowRay(
        intersectionPoint + (normal * 0.01),
        lightDir
    );
    const double closestHit = world.hit(shadowRay, primitives);

    if (closestHit < (mBaseOrigin - intersectionPoint).length()) {
        return Color(0.0, 0.0, 0.0);
    }
    return mBaseColor * world.getDistance(
        mBaseOrigin, intersectionPoint
    );
}