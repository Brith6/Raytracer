/*
** EPITECH PROJECT, 2025
** rautracer
** File description:
** primitive_fact.cpp
*/

#include "Primitive_fact.hpp"
#include "../src/primitives/plane/Plane.hpp"
#include "../src/primitives/sphere/Sphere.hpp"
#include "Plane.hpp"
#include "ErrorHandler.hpp"
#include "../core/Math.hpp"
#include "../core/Color.hpp"
#include <map>
#include <cmath>

namespace raytracer {
    std::vector<Plane> PrimitiveFact::createPlane(const libconfig::Setting& setting, ErrorHandler& errors) {
        std::vector<Plane> planes;

        if (setting.isList()) {
            for (int i = 0; i < setting.getLength(); ++i) {
                auto plane = parseSinglePlane(setting[i], errors);
                if (plane) {
                    planes.push_back(*plane);
                }
            }
        } else {
            auto plane = parseSinglePlane(setting, errors);
            if (plane) {
                planes.push_back(*plane);
            }
        }

        return planes;
    }

    static std::unique_ptr<Plane> parseSinglePlane(const libconfig::Setting& setting, ErrorHandler& errors) {
        std::string axis;
        int position;
        int cr, cg, cb;
        std::string rotationAxis;
        float rotationAngle = 0.0f;
        float translationX = 0.0f, translationY = 0.0f, translationZ = 0.0f;

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

        if (setting.lookupValue("rotationAxis", rotationAxis)) {
            if (rotationAxis != "X" && rotationAxis != "Y" && rotationAxis != "Z") {
                errors.report("Invalid rotation axis for plane: must be X, Y, or Z");
                return nullptr;
            }
            if (!setting.lookupValue("rotationAngle", rotationAngle)) {
                errors.report("Missing rotation angle for plane");
                return nullptr;
            }
        }

        setting.lookupValue("translationX", translationX);
        setting.lookupValue("translationY", translationY);
        setting.lookupValue("translationZ", translationZ);

        math::Vector3D rotationVector(0, 0, 0);
        if (rotationAxis == "X") {
            rotationVector.x = rotationAngle;
        } else if (rotationAxis == "Y") {
            rotationVector.y = rotationAngle;
        } else if (rotationAxis == "Z") {
            rotationVector.z = rotationAngle;
        }

        map<string, math::Matrix<double>> allMatrix;
        if (!rotationAxis.empty()) {
            math::Matrix<double> rotationMatrix(4, 4);
            if (rotationAxis == "X") {
                double rad = rotationAngle * M_PI / 180.0;
                rotationMatrix = math::Matrix<double>(4, 4, {
                    1, 0, 0, 0,
                    0, cos(rad), -sin(rad), 0,
                    0, sin(rad), cos(rad), 0,
                    0, 0, 0, 1
                });
            } else if (rotationAxis == "Y") {
                double rad = rotationAngle * M_PI / 180.0;
                rotationMatrix = math::Matrix<double>(4, 4, {
                    cos(rad), 0, sin(rad), 0,
                    0, 1, 0, 0,
                    -sin(rad), 0, cos(rad), 0,
                    0, 0, 0, 1
                });
            } else if (rotationAxis == "Z") {
                double rad = rotationAngle * M_PI / 180.0;
                rotationMatrix = math::Matrix<double>(4, 4, {
                    cos(rad), -sin(rad), 0, 0,
                    sin(rad), cos(rad), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                });
            }
            allMatrix["rotation"] = rotationMatrix;
        }
        math::Matrix<double> translationMatrix(4, 4, {
            1, 0, 0, translationX,
            0, 1, 0, translationY,
            0, 0, 1, translationZ,
            0, 0, 0, 1
        });
        allMatrix["translation"] = translationMatrix;
        auto plane = std::make_unique<Plane>(axis, position, Color{cr, cg, cb}, rotationVector, allMatrix);
        return plane;
        //return std::make_unique<Plane>(axis, position, Color{cr, cg, cb});
    }

    std::vector<Sphere> PrimitiveFact::createSphere(const libconfig::Setting& setting, ErrorHandler& errors) {
        std::vector<Sphere> spheres;

        if (setting.isList()) {
            for (int i = 0; i < setting.getLength(); ++i) {
                auto sphere = parseSingleSphere(setting[i], errors);
                if (sphere) {
                    spheres.push_back(*sphere);
                }
            }
        } else {
            auto sphere = parseSingleSphere(setting, errors);
            if (sphere) {
                spheres.push_back(*sphere);
            }
        }

        return spheres;
    }

    static std::unique_ptr<Sphere> parseSingleSphere(const libconfig::Setting& setting, ErrorHandler& errors) {
        double x, y, z, r;
        int cr, cg, cb;
        std::string rotationAxis;
        float rotationAngle = 0.0f;
        float translationX = 0.0f, translationY = 0.0f, translationZ = 0.0f;

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

        if (setting.lookupValue("rotationAxis", rotationAxis)) {
            if (rotationAxis != "X" && rotationAxis != "Y" && rotationAxis != "Z") {
                errors.report("Invalid rotation axis for sphere: must be X, Y, or Z");
                return nullptr;
            }
            if (!setting.lookupValue("rotationAngle", rotationAngle)) {
                errors.report("Missing rotation angle for sphere");
                return nullptr;
            }
        }

        setting.lookupValue("translationX", translationX);
        setting.lookupValue("translationY", translationY);
        setting.lookupValue("translationZ", translationZ);

    
        math::Vector3D rotationVector(0, 0, 0);
        if (rotationAxis == "X") {
            rotationVector.x = rotationAngle;
        } else if (rotationAxis == "Y") {
            rotationVector.y = rotationAngle;
        } else if (rotationAxis == "Z") {
            rotationVector.z = rotationAngle;
        }

        map<string, math::Matrix<double>> allMatrix;
        if (!rotationAxis.empty()) {
            math::Matrix<double> rotationMatrix(4, 4);
            if (rotationAxis == "X") {
                double rad = rotationAngle * M_PI / 180.0;
                rotationMatrix = math::Matrix<double>(4, 4, {
                    1, 0, 0, 0,
                    0, cos(rad), -sin(rad), 0,
                    0, sin(rad), cos(rad), 0,
                    0, 0, 0, 1
                });
            } else if (rotationAxis == "Y") {
                double rad = rotationAngle * M_PI / 180.0;
                rotationMatrix = math::Matrix<double>(4, 4, {
                    cos(rad), 0, sin(rad), 0,
                    0, 1, 0, 0,
                    -sin(rad), 0, cos(rad), 0,
                    0, 0, 0, 1
                });
            } else if (rotationAxis == "Z") {
                double rad = rotationAngle * M_PI / 180.0;
                rotationMatrix = math::Matrix<double>(4, 4, {
                    cos(rad), -sin(rad), 0, 0,
                    sin(rad), cos(rad), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                });
            }
            allMatrix["rotation"] = rotationMatrix;
        }
        math::Matrix<double> translationMatrix(4, 4, {
            1, 0, 0, translationX,
            0, 1, 0, translationY,
            0, 0, 1, translationZ,
            0, 0, 0, 1
        });
        allMatrix["translation"] = translationMatrix;
    
        auto sphere = std::make_unique<Sphere>(math::Point3D{x, y, z}, static_cast<float>(r), Color{cr, cg, cb}, rotationVector, allMatrix);
        return sphere;

        //return std::make_unique<Sphere>(math::Point3D{x, y, z}, static_cast<float>(r), Color{cr, cg, cb});
    }
}