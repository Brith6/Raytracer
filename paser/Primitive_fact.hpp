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

namespace raytracer {
    class PrimitiveFact {
    public:
        static std::unique_ptr<IPrimitives> createPrimitive(const libconfig::Setting& setting, const std::string& type);

    private:
        static std::unique_ptr<IPrimitives> createSphere(const libconfig::Setting& setting);
        static std::unique_ptr<IPrimitives> createPlane(const libconfig::Setting& setting);
    };
}

#endif
