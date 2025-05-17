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
        } catch (const libconfig::FileIOException& fioex) {
            errors_.report("I/O error while reading file: " + filename);
        } catch (const libconfig::ParseException& pex) {
            errors_.report("Parse error at " + std::string(pex.getFile()) + ":" +
                           std::to_string(pex.getLine()) + " - " + pex.getError());
        }
}

bool raytracer::Parser::parse(Scene& scene) {
    try {
        if (!parseCamera(scene)) {
            return false;
        }
        if (!parseLights(scene)) {
            return false;
        }
        auto planes = parsePlanes();
        auto spheres = parseSpheres();
        for (const auto& plane : planes) {
            scene.addPlane(plane);
        }
        for (const auto& sphere : spheres) {
            scene.addSphere(sphere);
        }
        return true;
    } catch (const libconfig::SettingException& ex) {
        errors_.report("Setting error: " + std::string(ex.what()));
        return false;
    }
}

bool raytracer::Parser::parseCamera(Scene& scene)
{
    try {
        const libconfig::Setting& cam = cfg_.lookup("camera");
        Vect or3 pos, look;
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

std::vector<Plane> raytracer::Parser::parsePlanes()
{
    std::vector<Plane> planes;

    if (!cfg_.exists("primitives") || !cfg_.getRoot()["primitives"].exists("planes")) {
        return planes;
    }

    const libconfig::Setting& planes_setting = cfg_.getRoot()["primitives"]["planes"];
    planes = PrimitiveFact::createPlane(planes_setting, errors_);
    return planes;
}

std::vector<Sphere> raytracer::Parser::parseSpheres()
{
    std::vector<Sphere> spheres;

    if (!cfg_.exists("primitives") || !cfg_.getRoot()["primitives"].exists("spheres")) {
        return spheres;
    }

    const libconfig::Setting& spheres_setting = cfg_.getRoot()["primitives"]["spheres"];
    spheres = PrimitiveFact::createSphere(spheres_setting, errors_);
    return spheres;
}