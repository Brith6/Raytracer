/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** ILight.hpp
*/

#pragma once

#include <iostream>
#include "../core/helpers/Color.hpp"
#include "../primitives/IPrimitive.hpp"
#include "../core/helpers/World.hpp"
#include <memory>

using std::unique_ptr;

namespace raytracer {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual Color getColorShadow(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const vector<unique_ptr<IPrimitive>> &primitives
            ) = 0;

            math::Point3D mBaseOrigin;
            math::Vector3D mBaseDirection;
            Color mBaseColor;
            math::Vector3D mBaseVectorRotation;
    };
}
