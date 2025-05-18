/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** directionalLigth.hpp
*/

#pragma once
#include "../ILigths.hpp"
#include <algorithm>

using std::map;
namespace raytracer {

    class DirectionalLight : public ILigths {
        public:
            DirectionalLight() = default;
            DirectionalLight(const double diffuse, const math::Point3D origin,
                math::Vector3D direction, const Color color, const math::Vector3D rotation,
                const map<string, math::Matrix<double>> &allMatrix)
                : _diffuse(diffuse), _origin(origin),
                _direction(direction), _color(color),
                _rotation(rotation), _allMatrix(allMatrix) {};
            ~DirectionalLight() = default;

            Color directLight(World &world, HitData &data,
                Color &color, const vector<std::unique_ptr<IPrimitives>> &primitives) override;

            double _diffuse;
            math::Point3D _origin;
            math::Vector3D _direction;
            Color _color;
            std::string _name;
            math::Vector3D _rotation;
            map<string, math::Matrix<double>> _allMatrix;

    };
}