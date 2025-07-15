/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Ray.hpp
*/

#pragma once

#include "../math/Math.hpp"

namespace raytracer {
    class Ray {
        public:
            Ray() = default;
            Ray(const math::Point3D &origin, const math::Vector3D &direction)
                : mOrigin(origin), mDirection(direction) {}
            ~Ray() = default;

            math::Point3D mOrigin = {0, 0, 0};
            math::Vector3D mDirection = {0, 0, 1};
    };
}
