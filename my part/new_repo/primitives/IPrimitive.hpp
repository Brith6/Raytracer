/*
** EPITECH PROJECT, 2025
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
        virtual ~IPrimitive() = default;

        virtual double hits(const Ray &ray) const = 0;
        virtual math::Vector3D getNormal(const math::Point3D &point) const = 0;
        virtual Color getColor() const = 0;
    };
}