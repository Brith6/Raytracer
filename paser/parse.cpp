/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** parsing
*/

#include "parse.hpp"
#include "Primitive_fact.hpp"
#include "ErrorHandler.hpp"
#include "Scene.hpp"
#include <libconfig.h++>
#include "../src/core/Color.hpp"
#include "../src/camera/Camera.hpp"
#include "../src/core/Math.hpp"
#include <map>
#include <string>

using libconfig::Setting;
using math::Vector3D;
using math::Point3D;
using Matrix4 = std::array<std::array<double, 4>, 4>;

namespace raytracer {

Parser::Parser(const std::string& filename, ErrorHandler& errorHandler)
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

bool Parser::parse(Scene& scene) {
    try {
        if (!parseCamera(scene)) return false;
        if (!parseLights(scene)) return false;
        auto planes = parsePlanes();
        auto spheres = parseSpheres();
        for (const auto& plane : planes) scene.addPlane(plane);
        for (const auto& sphere : spheres) scene.addSphere(sphere);
        return true;
    } catch (const libconfig::SettingException& ex) {
        errors_.report("Setting error: " + std::string(ex.what()));
        return false;
    }
}

bool Parser::parseCamera(Scene& scene)
{
    try {
        const Setting& cam = cfg_.lookup("camera");
        int width = cam["resolution"]["width"];
        int height = cam["resolution"]["height"];
        float px = cam["position"]["x"];
        float py = cam["position"]["y"];
        float pz = cam["position"]["z"];
        float lx = cam["look_at"]["x"];
        float ly = cam["look_at"]["y"];
        float lz = cam["look_at"]["z"];
        float fov;
        cam.lookupValue("fieldOfView", fov);
        Camera c;
        c.width = width;
        c.height = height;
        c._position = Point3D{px, py, pz};
        c.fieldOfView = fov;
        scene.setCamera(c);
    } catch (const libconfig::SettingException& e) {
        errors_.report("Camera parsing error: " + std::string(e.what()));
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
}
