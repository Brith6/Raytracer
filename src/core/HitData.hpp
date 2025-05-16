/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** HitData.hpp
*/

#pragma once
#include "Math.hpp"
#include <memory>

namespace raytracer {

    class HitData {
        public:
            math::Point3D p;
            math::Vector3D normal;
            float t;
            bool outside;
            float u;
            float v;
    };
}