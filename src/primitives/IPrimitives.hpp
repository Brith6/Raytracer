/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** IPrimitives.hpp
*/

#pragma once
#include <string>
#include "../core/Ray.hpp"
#include "../core/HitData.hpp"
#include "../core/Range.hpp"

namespace raytracer {
    class IPrimitives {
        public:
            IPrimitives() = default;
            virtual ~IPrimitives() = default;
            virtual bool hits(const Ray& ray, HitData& hitData) const = 0;
            virtual math::Vector3D getNormal(const math::Point3D &point) const = 0;
    };
}