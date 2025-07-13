/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** ILight.hpp
*/

#pragma once

#include "../core/helpers/Color.hpp"
#include "../primitives/IPrimitive.hpp"
#include <iostream>
#include <memory>

namespace raytracer
{
    class ILight {
        public:
            virtual ~ILight() = default;

            // The contract for all lights: calculate the color contribution
            virtual Color calculateContribution(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const std::vector<std::unique_ptr<IPrimitive>>& primitives
            ) const = 0;
        }; 
}