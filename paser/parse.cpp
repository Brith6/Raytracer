/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** parsing
*/

#include "parser.hpp"
#include "Primitive_fact.hpp"
#include "ErrorHandler.hpp"

Parser::Parser(const std::string& filename, ErrorHandler& errorHandler)
    : errors_(errorHandler)
{
}

bool Parser::parse(Scene& scene)
{
}

bool Parser::parseCamera(Scene& scene)
{
}

bool Parser::parseLights(Scene& scene)
{
}

bool Parser::parsePrimitives(Scene& scene)
{
    const libconfig::Setting& primitives = cfg_.lookup("primitives");
    bool primi = false;

    if (primitives.exists("spheres")) {
        const libconfig::Setting& spheres = primitives["spheres"];
        if (!spheres.isList()) {
            errors_.report("Spheres must be a list");
            return false;
        }
        for (int i = 0; i < spheres.getLength(); ++i) {
            auto primitive = PrimitiveFactory::createPrimitive(spheres[i], "sphere", errors_);
            if (primitive) {
                scene.addPrimitive(std::move(primitive));
                primi = true;
            }
        }
    }

    if (primitives.exists("planes")) {
        const libconfig::Setting& planes = primitives["planes"];
        if (!planes.isList()) {
            errors_.report("Planes must be a list");
            return false;
        }
        for (int i = 0; i < planes.getLength(); ++i) {
            auto primitive = PrimitiveFactory::createPrimitive(planes[i], "plane", errors_);
            if (primitive) {
                scene.addPrimitive(std::move(primitive));
                primi = true;
            }
        }
    }

    return primi;
}
