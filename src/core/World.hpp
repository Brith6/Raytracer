/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** World.hpp
*/

#pragma once
#include "../primitives/IPrimitives.hpp"
#include "../ligths/ILigths.hpp"
#include "Range.hpp"
#include <vector>
#include <memory>
#include <limits>

namespace raytracer {

    class World {
    public:
        World() = default;
        ~World() = default;

        double hit(const Ray &r,
            const vector<std::unique_ptr<IPrimitives>> &primitives) const {
            HitData tmp;
            float closest = std::numeric_limits<float>::max();
            double hitResult = 0.0;
    
            for (const auto &obj : primitives) {
                if (obj->hits(r, tmp) && (tmp.t > 0.0) && (tmp.t < closest)) {
                    
                    closest = tmp.t;
                }
            }
            return closest;
        }
    };

}
