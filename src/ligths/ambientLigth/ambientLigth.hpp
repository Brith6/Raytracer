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
            AmbientLight() = default;
            AmbientLight(double ambient,const Color color) : _color(color), _ambient(ambient) {};
            ~AmbientLight() = default;

            Color directLight(World &world, HitData &data,
                Color &color, const vector<std::unique_ptr<IPrimitives>> &primitives) override;

            double _ambient;
            Color _color;
            std::string _name;
    };
}