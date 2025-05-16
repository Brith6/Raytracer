/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

math::Point3D raytracer::Camera::ScreenPos(
    const double u, const double v) const
{
    math::Point3D screenPos = _screen.pointAt(u, v);

    screenPos.x += _position.x;
    screenPos.y += _position.x;
    return screenPos;
}

math::Vector3D raytracer::Camera::Direction(
    const math::Point3D &screenPos) const
{
    math::Vector3D dir = screenPos - _position;

    dir.normalize();
    return dir;
}

raytracer::Ray raytracer::Camera::ray(const double u, const double v) const
{
    const math::Point3D screenPos = ScreenPos(u, v);
    const math::Vector3D dir = Direction(screenPos);

    return Ray(_origin, dir);
}