/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** directionalLigth.hpp
*/

#pragma once
#include "../ILigths.hpp"
#include <algorithm>

namespace raytracer {

    class DirectionalLight : public ILigths {
        public:
            DirectionalLight() : _diffuse(0.0), _origin(math::Point3D(0, 0, 0)),
            _direction(math::Vector3D(0, 0, 0)), _color(Color(0, 0, 0)) {};
            DirectionalLight(const double diffuse, const math::Point3D origin,
                math::Vector3D direction, const Color color, const math::Vector3D rotation,
                const map<string, math::Matrix<double>> &allMatrix)
                : _diffuse(diffuse), _origin(origin),
                _direction(direction), _color(color),
                _rotation(rotation), _allMatrix(allMatrix) {};
            ~DirectionalLight() = default;

            Color directLight(World &world, HitData &data, Color &color) override;

            // void setName(const std::string &name) override { _name = name; }
            // std::string getName() const override { return _name; }

        // private:
            double _diffuse;
            math::Point3D _origin;
            math::Vector3D _direction;
            Color _color;
            std::string _name;
            math::Vector3D _rotation;
            map<string, math::Matrix<double>> _allMatrix;

    };
}