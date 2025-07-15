/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** World.hpp
*/

#pragma once
#include "../../primitives/IPrimitive.hpp"
#include "../../lights/ILight.hpp"
#include <vector>
#include <memory>
#include <limits>

namespace raytracer {

    class World {
    public:
        World() = default;
        ~World() = default;

        double getDistance(const math::Point3D borigin,
            const math::Point3D &intersectionPoint) const {
            const double distance = (borigin - intersectionPoint).length();
            const double attenuation = 1.0 / distance;

            return attenuation;
        }
        double hit(const Ray &r,
            const vector<std::unique_ptr<IPrimitive>> &primitives) const {
            double closest = std::numeric_limits<double>::max();
            double hitResult = 0.0;
    
            for (const auto &obj : primitives) {
                hitResult = obj.get()->hits(r);
                if (hitResult > 0.0 && hitResult < closest)
                    closest = hitResult;
            }
            return closest;
        }
    };

}
