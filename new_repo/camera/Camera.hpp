/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Camera.hpp
*/

#pragma once

#include "../core/helpers/Ray.hpp"
#include "../core/helpers/Rectangle3D.hpp"
#include "../core/math/Matrix.hpp"

namespace raytracer {

    class Camera {
    public:
        Camera() = default;

        Camera(
            const math::Point3D& origin,
            const math::Point3D& lookAt,
            const math::Vector3D& worldUp,
            double verticalFov,
            double aspectRatio
        ) {
            auto theta = verticalFov * M_PI / 180.0;
            auto h = tan(theta / 2.0);
            auto viewportHeight = 2.0 * h;
            auto viewportWidth = aspectRatio * viewportHeight;
            auto w = math::Vector3D::normalized(origin - lookAt);
            auto u = math::Vector3D::normalized(worldUp.cross(w));
            auto v = w.cross(u);
            _origin = origin;
            math::Vector3D horizontal = u * viewportWidth;
            math::Vector3D vertical = v * viewportHeight;
            math::Point3D lowerLeftCorner = _origin - (horizontal / 2.0) - (vertical / 2.0) - w;
            _screen = Rectangle3D(lowerLeftCorner, horizontal, vertical);
        }
        // Camera(const math::Point3D& position, double fieldOfView, int width, int height)
        // {
        //     double fovInRadians = fieldOfView * (M_PI / 180.0);
        //     const double screenDistance = 1.0 / (2.0 * ::tan(fovInRadians / 2.0));
        //     const double aspectRatio = static_cast<double>(width) / static_cast<double>(height);

        //     posZ = position.z;
        //     const double screenZ = position.z - screenDistance;
        //     const math::Point3D screenOrigin(position.x, position.y, screenZ);

        //     const math::Vector3D bottomSide(-aspectRatio, -1.0, screenZ);
        //     const math::Vector3D leftSide(aspectRatio, 1.0, screenZ);
        //     _screen = Rectangle3D(screenOrigin, bottomSide, leftSide);

        //     _origin = screenOrigin;
        // }
        Ray ray(double u, double v) const {
            math::Point3D target = _screen.pointAt(u, v);
            // target.x += _origin.x;
            // target.y += _origin.y;
            // const math::Point3D camPos(_origin.x, _origin.y, posZ);
            math::Vector3D direction = math::Vector3D::normalized(target - _origin);
            return Ray(_origin, direction);
        }

    protected:
        math::Point3D _origin;
        Rectangle3D _screen;
        double posZ = 0.0;
    };
}
