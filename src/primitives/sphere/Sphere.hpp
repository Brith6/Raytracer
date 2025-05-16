/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Sphere.hpp
*/

#pragma once
#include "../IPrimitives.hpp"
#include "../../core/Color.hpp"

namespace raytracer {
    class Sphere : public IPrimitives {
        public:
            Sphere(const math::Point3D& center, float radius, const Color& color)
                : _center(center), _radius(radius), _color(color) {}
            ~Sphere() override = default;

            bool hits(const Ray& ray, HitData& hitData) const override;
            math::Vector3D getNormal(const math::Point3D &point) const override;
            // void setName(const std::string &name) override { _name = name; }
            // std::string getName() const override { return _name; }

        private:
            math::Point3D _center;
            float _radius;
            Color _color;
            std::string _name;
    };
}