/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLigth.hpp
*/

#pragma once
#include "../ILigths.hpp"
#include <algorithm>

using std::map;
namespace raytracer {

    class PointLight : public ILigths {
        public:
            PointLight() = default;
            PointLight(const double diffuse, math::Point3D origin, const Color color
                ,const math::Vector3D rotation,
                const map<string, math::Matrix<double>> &allMatrix)
                : _diffuse(diffuse), _origin(origin), _color(color),
                _rotation(rotation), _allMatrix(allMatrix) {};
            ~PointLight() = default;

            Color directLight(World &world, HitData &data,
                Color &color, const vector<std::unique_ptr<IPrimitives>> &primitives) override;

            double _diffuse;
            math::Point3D _origin;
            Color _color;
            math::Vector3D _rotation;
            map<string, math::Matrix<double>> _allMatrix;
            std::string _name;
    };
}