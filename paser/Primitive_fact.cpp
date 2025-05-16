/*
** EPITECH PROJECT, 2025
** rautracer
** File description:
** primitive_fact.cpp
*/

#include "Primitive_fact.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "../ErrorHandler.hpp"
#include "../core/Math.hpp"
#include "../core/Color.hpp"

namespace raytracer {
    std::unique_ptr<IPrimitives> PrimitiveFactory::createPrimitive(const libconfig::Setting& setting, const std::string& type, ErrorHandler& errors) {
        if (type == "sphere") {
            return createSphere(setting, errors);
        } else if (type == "plane") {
            return createPlane(setting, errors);
        }
        errors.report("Unknown primitive type: " + type);
        return nullptr;
    }

    std::unique_ptr<IPrimitives> PrimitiveFactory::createSphere(const libconfig::Setting& setting, ErrorHandler& errors) {
        double x;
        double y;
        double z;
        double r;
        int cr;
        int cg;
        int cb;

        if (!setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("r", r)) {
            errors.report("Missing coordinates or radius for sphere");
            return nullptr;
        }
        if (!setting.exists("color") ||
            !setting["color"].lookupValue("r", cr) ||
            !setting["color"].lookupValue("g", cg) ||
            !setting["color"].lookupValue("b", cb)) {
            errors.report("Missing or invalid color for sphere");
            return nullptr;
        }
        if (r <= 0) {
            errors.report("Invalid radius for sphere: must be positive");
            return nullptr;
        }
        if (cr < 0 || cr > 255 || cg < 0 || cg > 255 || cb < 0 || cb > 255) {
            errors.report("Invalid color values for sphere: must be between 0 and 255");
            return nullptr;
        }

        return std::make_unique<Sphere>(math::Point3D{x, y, z}, static_cast<float>(r), Color{cr, cg, cb});
    }

    std::unique_ptr<IPrimitives> PrimitiveFactory::createPlane(const libconfig::Setting& setting, ErrorHandler& errors)
    {
        std::string axis;
        int position;
        int cr;
        int cg;
        int cb;

        if (!setting.lookupValue("axis", axis) ||
            !setting.lookupValue("position", position)) {
            errors.report("Missing axis or position for plane");
            return nullptr;
        }
        if (!setting.exists("color") ||
            !setting["color"].lookupValue("r", cr) ||
            !setting["color"].lookupValue("g", cg) ||
            !setting["color"].lookupValue("b", cb)) {
            errors.report("Missing or invalid color for plane");
            return nullptr;
        }
        if (axis != "X" && axis != "Y" && axis != "Z") {
            errors.report("Invalid axis for plane: must be X, Y, or Z");
            return nullptr;
        }
        if (cr < 0 || cr > 255 || cg < 0 || cg > 255 || cb < 0 || cb > 255) {
            errors.report("Invalid color values for plane: must be between 0 and 255");
            return nullptr;
        }

        return std::make_unique<Plane>(axis, position, Color{cr, cg, cb});
    }
}
