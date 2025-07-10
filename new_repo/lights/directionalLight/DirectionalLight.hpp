/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** DirectionalLight.hpp
*/

#pragma once
#include "../ILight.hpp"

namespace raytracer
{
    class DirectionalLight : public ILight 
    {
        public:
            DirectionalLight() = default;
            DirectionalLight(const math::Vector3D& direction, const Color& color)
                : _direction(math::Vector3D::normalized(direction)), _color(color) {}    
            ~DirectionalLight() override = default;

            Color calculateContribution(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const std::vector<std::unique_ptr<IPrimitive>>& primitives
            ) const override;

        private:
            double checkShadow(
                const Ray &shadowRay,
                const std::vector<std::unique_ptr<IPrimitive>>& primitives
            ) const;

        protected:
            math::Vector3D _direction;
            Color _color;
    };   
}