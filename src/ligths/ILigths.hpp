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
#include <map>

namespace raytracer {
    class ILigths {
        public:
            ILigths() = default;
            virtual ~ILigths() = default;
            virtual Color directLight(World &world, HitData &data, Color &color) = 0;

            math::Point3D _borigin;
            math::Vector3D _bdirection;
            Color _bcolor;
            math::Vector3D _brotation;
            double _bdiffuse;
            double _bambient;
    };
}