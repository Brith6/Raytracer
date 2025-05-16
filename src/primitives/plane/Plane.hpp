/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Plane.hpp
*/

#pragma once
#include "../IPrimitives.hpp"
#include "../../core/Color.hpp"

namespace raytracer {
    class Plane : public IPrimitives {
        public:
            Plane(const std::string &axis, const int position, const Color &color)
                : _axis(axis), _position(position), _color(color) {}
            ~Plane() override = default;

            bool hits(const Ray& ray, HitData& hitData) const override;
            bool checkRayPlaneIntersection(const Ray &ray,
                const math::Point3D &position, HitData& hitData) const;
            // void setName(const std::string &name) override { _name = name; }
            // std::string getName() const override { return _name; }
            math::Vector3D getNormal(const math::Point3D &point) const;

        private:
            std::string _axis;
            int _position = 0;
            Color _color;
            std::string _name;
    };
}