/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Sphere.hpp
*/

#pragma once
#include "../IPrimitives.hpp"
#include "../../core/Color.hpp"

using std::map;
namespace raytracer {
    class Sphere : public IPrimitives {
        public:
            Sphere() = default;
            Sphere(const math::Point3D& center, float radius, const Color& color,
                math::Vector3D &rotation,
                const map<string, math::Matrix<double>> &allMatrix)
                : _center(center), _radius(radius), _color(color),
                _rotation(rotation), _allMatrix(allMatrix) {}
            ~Sphere() override = default;

            bool hits(const Ray& ray, HitData& hitData) const override;
            math::Vector3D getNormal(const math::Point3D &point) const override;

            math::Point3D _center;
            float _radius;
            Color _color;
            math::Vector3D _rotation;
            map<string, math::Matrix<double>> _allMatrix;
    };
}