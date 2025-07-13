/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Composite.hpp
*/

#pragma once
#include "../../primitives/IPrimitive.hpp"
#include "../core/helpers/Ray.hpp"
#include <vector>
#include <memory>
#include <limits>

namespace raytracer {
    class Composite {
    public:
        Composite() = default;
        ~Composite() = default;

        double getDistance(const math::Point3D borigin,
            const math::Point3D &intersectionPoint) const {
            const double distance = (borigin - intersectionPoint).length();
            const double attenuation = 1.0 / distance;
            return attenuation;
        }

        double hit(const Ray &r,
            const std::vector<std::unique_ptr<IPrimitive>> &primitives) const {
            double closest = std::numeric_limits<double>::max();
            double hitResult = 0.0;

            for (const auto &obj : primitives) {
                hitResult = obj->hits(r);
                if (hitResult > 0.0 && hitResult < closest) {
                    closest = hitResult;
                }
            }
            return closest;
        }
    }
}