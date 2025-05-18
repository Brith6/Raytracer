/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Plane.hpp
*/

#pragma once
#include "../IPrimitives.hpp"
#include "../../core/Color.hpp"

using std::map;
namespace raytracer {
    class Plane : public IPrimitives {
        public:
            Plane() = default;
            Plane(const std::string &axis, const int position, const Color &color,
                const math::Vector3D &rotation,
                const std::map<std::string, math::Matrix<double>> &allMatrix)
                : _axis(axis), _position(position), _color(color), _rotation(rotation),
                _allMatrix(allMatrix) {}
            ~Plane() override = default;

            bool hits(const Ray& ray, HitData& hitData) const override;
            bool checkRayPlaneIntersection(const Ray &ray,
                const math::Point3D &position, HitData& hitData) const;
            math::Vector3D getNormal(const math::Point3D &point) const;

            std::string _axis = "Z";
            int _position = 0;
            math::Vector3D _rotation;
            Color _color;
            map<string, math::Matrix<double>> _allMatrix;
    };
}