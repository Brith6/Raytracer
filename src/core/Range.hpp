/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Range.hpp
*/

#pragma once
#include <algorithm>

namespace math
{
    class Range {
        public:
            Range() = default;
            Range(float min, float max) : _min(min), _max(max) {};
            ~Range() = default;

            bool isInRange(float value) const { return value >= _min && value <= _max; }
            float clamp(float value) const { return std::max(_min, std::min(value, _max)); }

            float _min;
            float _max;
    };
}