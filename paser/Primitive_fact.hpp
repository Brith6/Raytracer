/*
** EPITECH PROJECT, 2025
** rautracer
** File description:
** primitive_fact.hpp
*/

#ifndef PRIMITIVE_FACT_HPP
    #define PRIMITIVE_FACT_HPP

#include "../src/primitives/IPrimitives.hpp"
#include <libconfig.h++>
#include <memory>
#include <string>
#include <vector>
#include "../src/primitives/plane/Plane.hpp"
#include "../src/primitives/sphere/Sphere.hpp"
#include "ErrorHandler.hpp"

namespace raytracer {
    class PrimitiveFact {
    public:
        static std::vector<std::unique_ptr<Plane>> createPlane(const libconfig::Setting& setting, ErrorHandler& errors);
        static std::vector<std::unique_ptr<Sphere>> createSphere(const libconfig::Setting& setting, ErrorHandler& errors);
    };
}

#endif
