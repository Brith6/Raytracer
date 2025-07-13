/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Rectangle3D.hpp
*/


#pragma once

#include <iostream>
#include "../math/Math.hpp"

namespace raytracer {
    class Rectangle3D {
        public:
            Rectangle3D() = default;
            Rectangle3D(const math::Point3D &origin,
                const math::Vector3D &bottomSide,
                const math::Vector3D &leftSide)
                : _origin(origin), _bottomSide(bottomSide),
                _leftSide(leftSide) {}
            ~Rectangle3D() = default;

            math::Point3D pointAt(double u, double v) const {
                return _origin + (_bottomSide * u) + (_leftSide * v);
            }
        private:
            math::Point3D _origin;
            math::Vector3D _bottomSide; // axe x
            math::Vector3D _leftSide; // axe y
    };
}
