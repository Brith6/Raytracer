/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** parsing
*/

#include "parse.hpp"
#include "Primitive_fact.hpp"
#include "ErrorHandler.hpp"

raytracer::Parser::Parser(const std::string& filename, ErrorHandler& errorHandler)
    : errors_(errorHandler)
{
    try {
        cfg_.readFile(filename.c_str());
    } catch (const libconfig::FileIOException&) {
        errors_.add("Cannot read file: " + filename);
    } catch (const libconfig::ParseException& pe) {
        errors_.add(pe.getFile() + ":" +
                    std::to_string(pe.getLine()) +
                    " - " + pe.getError());
    }
}

bool raytracer::Parser::parse(Scene& scene)
{
    if (errors_.hasErrors())
        return false;
    return parseCamera(scene)
        && parseLights(scene)
        && parsePrimitives(scene);
}

bool raytracer::Parser::parseCamera(Scene& scene)
{
    try {
        const libconfig::Setting& cam = cfg_.lookup("camera");
        Vector3 pos, look;
        cam.lookupValue("position", pos);
        cam.lookupValue("look_at", look);
        scene.setCamera(Camera{pos, look});
    } catch (const libconfig::SettingException& e) {
        errors_.add("Camera error: " + std::string(e.what()));
        return false;
    }
    return true;
}

bool raytracer::Parser::parseLights(Scene& scene)
{
    try {
        const libconfig::Setting& lights = cfg_.lookup("lights");
        for (int i = 0; i < lights.getLength(); ++i) {
            const libconfig::Setting& l = lights[i];
            std::string type;
            float intensity;
            l.lookupValue("type", type);
            l.lookupValue("intensity", intensity);
            if (type == "ambient") {
                scene.addLight(std::make_unique<AmbientLight>(intensity));
            } else if (type == "directional") {
                Vector3 dir;
                l.lookupValue("direction", dir);
                scene.addLight(std::make_unique<DirectionalLight>(dir, intensity));
            }
        }
    } catch (const libconfig::SettingException& e) {
        errors_.add("Lights error: " + std::string(e.what()));
        return false;
    }
    return true;
}

bool raytracer::Parser::parsePrimitives(Scene& scene) {
    if (!cfg_.exists("primitives")) {
        errors_.report("No 'primitives' section found in configuration");
        return false;
    }

    const libconfig::Setting& primitives = cfg_.getRoot()["primitives"];

    if (primitives.exists("planes")) {
        auto planes = PrimitiveFact::createPlane(primitives["planes"], errors_);
        if (planes.empty()) {
            return false;
        }
        for (auto& plane : planes) {
            scene.addPlane(std::move(plane));
        }
    }

    if (primitives.exists("spheres")) {
        auto spheres = PrimitiveFact::createSphere(primitives["spheres"], errors_);
        if (spheres.empty()) {
            return false;
        }
        for (auto& sphere : spheres) {
            scene.addSphere(std::move(sphere));
        }
    }

    for (const auto& plane : scene.getPlanes()) {
        scene.addPrimitive(std::make_unique<Plane>(*plane));
    }
    for (const auto& sphere : scene.getSpheres()) {
        scene.addPrimitive(std::make_unique<Sphere>(*sphere));
    }

    return true;
}