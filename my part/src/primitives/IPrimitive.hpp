/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** IPrimitive.hpp
*/

#pragma once

#include "../core/helpers/Color.hpp"
#include "../core/helpers/Ray.hpp"
#include "../core/math/Math.hpp"
#include "../core/math/Matrix.hpp"
#include <iostream>
#include <map>
#include <vector>

using std::vector;
using std::string;
using std::map;

namespace raytracer {
    class IPrimitive {
        public:
            IPrimitive() = default;
            virtual ~IPrimitive() = default;

            virtual double hits(const Ray &ray) = 0;
            virtual math::Vector3D getNormal(const math::Point3D &point) const = 0;

            Color mBaseColor;
            math::Point3D mBaseCenter;
            int mBaseRadius;
            string mBaseAxis;
            int mBasePosition;
            int mBaseHeight;
            map<string, math::Matrix<double>> mBaseAllMatrix;
            math::Vector3D mBaseRotation;
    };
}
