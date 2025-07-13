/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Sphere.hpp
*/

#pragma once
#include "../IPrimitive.hpp"

namespace raytracer {
    class Sphere : public IPrimitive {
        public:
            Sphere() = default;
            Sphere(const math::Point3D center, double radius, const Color &color)
                : _center(center), _radius(radius), _color(color) {}

            ~Sphere() override = default;
            double hits(const Ray &ray) const override;
            math::Vector3D getNormal(const math::Point3D &point) const override;
            Color getColor() const override { return _color; }

        protected:
            math::Point3D _center;
            double _radius = 0.0;
            Color _color;
    };
}