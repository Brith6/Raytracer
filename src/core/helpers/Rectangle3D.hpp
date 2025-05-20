/*
** EPITECH PROJECT, 2024
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
                : mOrigin(origin), mBottomSide(bottomSide),
                mLeftSide(leftSide) {}
            ~Rectangle3D() = default;

            math::Point3D pointAt(double u, double v) const {
                math::Point3D bottomLeft(-mLeftSide.mX, 1, mOrigin.mZ);
                math::Vector3D horizontal(2 * mLeftSide.mX, 0, 0);
                math::Vector3D vertical(0, -2, 0);
            
                return bottomLeft + (horizontal * u) + (vertical * v);
            }
        private:
            math::Point3D mOrigin;
            math::Vector3D mBottomSide;
            math::Vector3D mLeftSide;
    };
}
