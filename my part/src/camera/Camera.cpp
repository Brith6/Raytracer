/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Camera.cpp
*/

#include "Camera.hpp"
#include "../core/helpers/Ray.hpp"
#include "../core/math/Math.hpp"
#include "../core/helpers/Rectangle3D.hpp"

math::Point3D raytracer::Camera::calculateScreenPos(
    const double u, const double v) const
{
    math::Point3D screenPos = mScreen.pointAt(u, v);

    screenPos.mX += posX;
    screenPos.mY += posY;
    return screenPos;
}

math::Vector3D raytracer::Camera::calculateDirection(
    const math::Point3D &screenPos) const
{
    const math::Point3D cameraPos(posX, posY, posZ);
    math::Vector3D dir = screenPos - cameraPos;

    dir.normalize();
    return dir;
}

raytracer::Ray raytracer::Camera::ray(const double u, const double v) const
{
    const math::Point3D screenPos = calculateScreenPos(u, v);
    const math::Vector3D dir = calculateDirection(screenPos);

    return Ray(mOrigin, dir);
}
