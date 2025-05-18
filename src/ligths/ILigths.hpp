/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** ILigths.hpp
*/

#pragma once
#include "../core/Color.hpp"
#include "../core/HitData.hpp"
#include "../core/World.hpp"

namespace raytracer {
    class ILigths {
        public:
            ILigths() = default;
            virtual ~ILigths() = default;
            
            virtual bool directLight(World &world, HitData &data, Color &color) = 0;
    };
}