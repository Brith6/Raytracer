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


bool Parser::parseDirectionalLights(const Setting& lights, Scene& scene)
{
    if (!lights.exists("directional")) return true;

    const Setting& list = lights["directional"];
    if (!list.isList()) {
        errors_.report("'directional' must be a list");
        return false;
    }

    for (int i = 0; i < list.getLength(); ++i) {
        const Setting& it = list[i];
        double diff;
        if (!it.lookupValue("intensity", diff)) {
            errors_.report("Missing intensity in directional light");
            return false;
        }

        const Setting& origin = it["origin"];
        const Setting& direction = it["direction"];
        const Setting& color = it["color"];
        double ox, oy, oz, dx, dy, dz;
        int cr, cg, cb;
        origin.lookupValue("x", ox);
        origin.lookupValue("y", oy);
        origin.lookupValue("z", oz);
        direction.lookupValue("x", dx);
        direction.lookupValue("y", dy);
        direction.lookupValue("z", dz);
        color.lookupValue("r", cr);
        color.lookupValue("g", cg);
        color.lookupValue("b", cb);
        Color col{
            static_cast<double>(cr),
            static_cast<double>(cg),
            static_cast<double>(cb)
        };
        std::map<std::string, Matrix4> allMatrix;
        Vector3D rotation{0, 0, 0};
        scene.addDirectionalLight(DirectionalLight{
            diff,
            Point3D{ox, oy, oz},
            Vector3D{dx, dy, dz},
            col,
            rotation,
            allMatrix
        });
    }

    return true;
}

bool Parser::parsePointLights(const Setting& lights, Scene& scene)
{
    if (!lights.exists("point")) return true;
    const Setting& list = lights["point"];
    if (!list.isList()) {
        errors_.report("'point' must be a list");
        return false;
    }
    for (int i = 0; i < list.getLength(); ++i) {
        const Setting& it = list[i];
        double diff;
        if (!it.lookupValue("intensity", diff)) {
            errors_.report("Missing intensity in point light");
            return false;
        }
        const Setting& origin = it["origin"];
        const Setting& color = it["color"];
        double ox;
        double oy;
        double oz;
        int cr;
        int cg;
        int cb;
        origin.lookupValue("x", ox);
        origin.lookupValue("y", oy);
        origin.lookupValue("z", oz);
        color.lookupValue("r", cr);
        color.lookupValue("g", cg);
        color.lookupValue("b", cb);
        Color col{
            static_cast<double>(cr),
            static_cast<double>(cg),
            static_cast<double>(cb)
        };
        std::map<std::string, Matrix4> allMatrix;
        Vector3D rotation{0, 0, 0};
        scene.addPointLight(PointLight{diff, Point3D{ox, oy, oz}, col, rotation, allMatrix});
    }
    return true;
}

bool Parser::parseAmbientLight(const Setting& lights, Scene& scene)
{
    if (lights.exists("ambient")) {
        double amb;
        lights.lookupValue("ambient", amb);
        scene.addAmbientLight(AmbientLight{amb, Color{1, 1, 1}});
    }
    return true;
}

bool Parser::parseLights(Scene& scene)
{
    try {
        const Setting& lights = cfg_.lookup("lights");

        if (!parseAmbientLight(lights, scene)) return false;
        if (!parsePointLights(lights, scene)) return false;
        if (!parseDirectionalLights(lights, scene)) return false;

    } catch (const libconfig::SettingException& e) {
        errors_.report("Lights parsing error: " + std::string(e.what()));
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
