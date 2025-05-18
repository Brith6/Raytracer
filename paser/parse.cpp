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
using std::cerr;
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

bool Parser::parseLights(Scene& scene)
{
    try {
        const Setting& lights = cfg_.lookup("lights");

        if (lights.exists("ambient")) {
            double amb;
            lights.lookupValue("ambient", amb);
            scene.addAmbientLight(AmbientLight{amb, Color{1, 1, 1}});
        }
        if (lights.exists("point")) {
            const Setting& list = lights["point"];
            if (list.isList()) {
                for (int i = 0; i < list.getLength(); ++i) {
                    const Setting& it = list[i];
                    double diff;
                    if (!it.lookupValue("diffuse", diff)) {
                        errors_.report("Missing diffuse in point light");
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
                    parseRotation(list, allMatrix, rotation);

                    scene.addPointLight(PointLight{diff, Point3D{ox, oy, oz}, col, rotation, allMatrix});
                }
            } else {
                errors_.report("'point' must be a list");
                return false;
            }
        }

        if (lights.exists("directional")) {
            const Setting& list = lights["directional"];
            if (list.isList()) {
                for (int i = 0; i < list.getLength(); ++i) {
                    const Setting& it = list[i];
                    double diff;
                    if (!it.lookupValue("diffuse", diff)) {
                        errors_.report("Missing diffuse in directional light");
                        return false;
                    }
                    const Setting& origin = it["origin"];
                    const Setting& direction = it["direction"];
                    const Setting& color = it["color"];
                    double ox;
                    double oy;
                    double oz;
                    double dx;
                    double dy;
                    double dz;
                    int cr;
                    int cg;
                    int cb;
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
                        col
                    });
                }
            } else {
                errors_.report("'directional' must be a list");
                return false;
            }
        }
    } catch (const libconfig::SettingException& e) {
        errors_.report("Lights parsing error: " + std::string(e.what()));
        return false;
    }
    return true;
}
void parseRotation(const libconfig::Setting &fileconfigRotation,
    map<string, math::Matrix<double>> &allMatrix,
    math::Vector3D &vectorRotation)
{
    double rotationX = 0.0;
    double rotationY = 0.0;
    double rotationZ = 0.0;
    try {
        const libconfig::Setting &rotation = fileconfigRotation["rotation"];
        try {
            rotationX = rotation["x"];
        } catch (const libconfig::ConfigException &) {
            try {
                rotationX = static_cast<double>(static_cast<int>(rotation["x"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found rotation in axe X or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            rotationY = rotation["y"];
        } catch (const libconfig::ConfigException &) {
            try {
                rotationY = static_cast<double>(static_cast<int>(rotation["y"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found rotation in axe Y or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            rotationZ = rotation["z"];
        } catch (const libconfig::ConfigException &) {
            try {
                rotationZ = static_cast<double>(static_cast<int>(rotation["z"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found rotation in axe Z or value incorrect\n";
                ::exit(84);
            }
        }
        rotationX = (rotationX * M_PI) / 180.0;
        rotationY = (rotationY * M_PI) / 180.0;
        rotationZ = (rotationZ * M_PI) / 180.0;
        allMatrix["rotationX"] = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, ::cos(rotationX), -::sin(rotationX), 0.0},
            {0, ::sin(rotationX), ::cos(rotationX), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
        allMatrix["rotationY"] = {
            {::cos(rotationY), 0.0, ::sin(rotationY), 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {-::sin(rotationY), 0, ::cos(rotationY), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
        allMatrix["rotationZ"] = {
            {::cos(rotationZ), -::sin(rotationZ), 0.0, 0.0},
            {::sin(rotationZ), ::cos(rotationZ), 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
    } catch (const libconfig::SettingNotFoundException &) {
    }
    vectorRotation = math::Vector3D(rotationX, rotationY, rotationZ);
}

void parseTranslation(const libconfig::Setting &fileconfigTranslation,
    map<string, math::Matrix<double>> &allMatrix)
{
    double translationX = 0;
    double translationY = 0;
    double translationZ = 0;
    try {
        const libconfig::Setting &translation = fileconfigTranslation["translation"];
        try {
            translationX = translation["x"];
        } catch (const libconfig::ConfigException &) {
            try {
                translationX = static_cast<double>(static_cast<int>(translation["x"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found translation in axe X or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            translationY = translation["y"];
        } catch (const libconfig::ConfigException &) {
            try {
                translationY = static_cast<double>(static_cast<int>(translation["y"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found translation in axe Y or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            translationZ = translation["z"];
        } catch (const libconfig::ConfigException &) {
            try {
                translationZ = static_cast<double>(static_cast<int>(translation["z"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found translation in axe Z or value incorrect\n";
                ::exit(84);
            }
        }
        allMatrix["translation"] = {
            {1.0, 0.0, 0.0, translationX},
            {0.0, 1.0, 0.0, translationY},
            {0.0, 0.0, 1.0, translationZ},
            {0.0, 0.0, 0.0, 1.0}
        };
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void parseScale(const libconfig::Setting &fileconfigScale,
    map<string, math::Matrix<double>> &allMatrix)
{
    double scaleX = 1.0;
    double scaleY = 1.0;
    double scaleZ = 1.0;
    try {
        const libconfig::Setting &scale = fileconfigScale["scale"];
        try {
            scaleX = scale["x"];
        } catch (const libconfig::ConfigException &) {
            try {
                scaleX = static_cast<double>(static_cast<int>(scale["x"]));
            } catch (const libconfig::ConfigException &) {
            }
        }
        try {
            scaleY = scale["y"];
        } catch (const libconfig::ConfigException &) {
            try {
                scaleY = static_cast<double>(static_cast<int>(scale["y"]));
            } catch (const libconfig::ConfigException &) {
            }
        }
        try {
            scaleZ = scale["z"];
        } catch (const libconfig::ConfigException &) {
            try {
                scaleZ = static_cast<double>(static_cast<int>(scale["z"]));
            } catch (const libconfig::ConfigException &) {
            }
        }
        allMatrix["scale"] = {
            {scaleX, 0.0, 0.0, 0.0},
            {0.0, scaleY, 0.0, 0.0},
            {0.0, 0.0, scaleZ, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void calcFinalTransformationMatrix(
    map<string, math::Matrix<double>> &allMatrix
)
{
    allMatrix["final"] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    if (allMatrix.find("translation") != allMatrix.end()) {
        allMatrix["final"] *= allMatrix["translation"];
    }
    if (allMatrix.find("scale") != allMatrix.end()) {
        allMatrix["final"] *= allMatrix["scale"];
    }
    if (allMatrix.find("rotation") != allMatrix.end()) {
        allMatrix["final"] *= allMatrix["rotation"];
    } else {
        if (allMatrix.find("rotationX") != allMatrix.end()) {
            allMatrix["final"] *= allMatrix["rotationX"];
            allMatrix["final"] *= allMatrix["rotationY"];
            allMatrix["final"] *= allMatrix["rotationZ"];
        }
    }
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
