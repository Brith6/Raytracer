/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLight.hpp
*/

#pragma once
#include "../ILight.hpp"

namespace raytracer {
    class PointLight : public ILight {
        public:
            PointLight() = default;
            PointLight(const math::Point3D& origin, const Color& color)
                : _origin(origin), _color(color) {}
            ~PointLight() override = default;

            Color calculateContribution(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const std::vector<std::unique_ptr<IPrimitive>>& primitives
            ) const override;

        protected:
            math::Point3D _origin;
            Color _color;
    };
}
