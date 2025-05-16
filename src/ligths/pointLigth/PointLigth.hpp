/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLigth.hpp
*/

#pragma once
#include "../ILigths.hpp"
#include <algorithm>

namespace raytracer {

    class PointLight : public ILigths {
        public:
            // PointLight() : _direction(math::Vector3D(0, 0, 0)), _color(Color(0, 0, 0)) {};
            PointLight(math::Point3D origin, const Color color)
                : _origin(origin), _color(color) {};
            ~PointLight() = default;

            bool directLight(World &world, HitData &data, Color &color) override;

            // void setName(const std::string &name) override { _name = name; }
            // std::string getName() const override { return _name; }

        private:
            math::Point3D _origin;
            Color _color;
            std::string _name;
    };
}