/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Plane.hpp
*/

#pragma once
#include "../IPrimitive.hpp"
#include <string>

namespace raytracer
{
    class Plane : public IPrimitive 
    {
        public:
            Plane() = default;
            Plane(const string &axis, double position, const Color &color)
                : _axis(axis), _position(position), _color(color) {}

            double hits(const Ray &ray) const override;
            math::Vector3D getNormal(const math::Point3D &point) const override;
            Color getColor() const override { return _color; }

        private:
            math::Point3D getPlanePoint() const;

        protected:
            string _axis = "Y";
            double _position = 0.0;
            Color _color;
    };
}