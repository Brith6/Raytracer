/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** ambientLigth.hpp
*/

#pragma once
#include "../ILigths.hpp"
#include <algorithm>

namespace raytracer {

    class AmbientLight : public ILigths {
        public:
            AmbientLight() : _color(Color(0, 0, 0)), _ambient(0.0) {};
            AmbientLight(double ambient,const Color color) : _color(color), _ambient(ambient) {};
            ~AmbientLight() = default;

            Color directLight(World &world, HitData &data, Color &color) override;

            // void setName(const std::string &name) override { _name = name; }
            // std::string getName() const override { return _name; }

        // private:
            // math::Vector3D _direction;
            double _ambient;
            Color _color;
            std::string _name;
    };
}