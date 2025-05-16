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
            DirectionalLight() : _direction(math::Vector3D(0, 0, 0)), _color(Color(0, 0, 0)) {};
            DirectionalLight(math::Vector3D direction, const Color color)
                : _direction(direction), _color(color) {};
            ~DirectionalLight() = default;

            bool directLight(World &world, HitData &data, Color &color) override;

            // void setName(const std::string &name) override { _name = name; }
            // std::string getName() const override { return _name; }

        private:
            math::Vector3D _direction;
            Color _color;
            std::string _name;
    };
}