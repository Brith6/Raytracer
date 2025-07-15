/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Parser.cpp
*/

#include "Parser.hpp"
#include "../core/designPatterns/Factory.hpp"
#include "../core/error/Error.hpp"
#include <libconfig.h++>
#include <filesystem>
#include <iostream>

namespace core {

    raytracer::Scene Parser::parseFile(const std::string &filename)
    {
        raytracer::Scene scene;
        libconfig::Config cfg;
        if (!std::filesystem::exists(filename)) {
            throw raytracer::ParseError("File not found: " + filename);
        }
        try {
            cfg.readFile(filename.c_str());
            std::string basePath = std::filesystem::path(filename).parent_path().string();
            processConfig(cfg, scene, basePath);
        } catch (const libconfig::FileIOException &) {
            throw raytracer::ParseError("I/O error while reading file: " + filename);
        } catch (const libconfig::ParseException &pex) {
            throw raytracer::ParseError("Parse error in " + std::string(pex.getFile()) + ":" + std::to_string(pex.getLine())
                                        + " - " + std::string(pex.getError()));
        }
        return scene;
    }
    

    void Parser::processConfig(const libconfig::Config &cfg, raytracer::Scene &scene, const std::string &basePath)
    {
        if (cfg.exists("import")) {
            const libconfig::Setting& imports = cfg.lookup("import");
            if (imports.isList()) {
                for (int i = 0; i < imports.getLength(); ++i) {
                    std::string importFile = imports[i];
                    std::filesystem::path importPath = basePath.empty() ? std::filesystem::path(importFile) : std::filesystem::path(basePath) / importFile;
                    raytracer::Scene importedScene = parseFile(importPath.string());
                    scene.primitives.insert(
                        scene.primitives.end(),
                        std::make_move_iterator(importedScene.primitives.begin()),
                        std::make_move_iterator(importedScene.primitives.end())
                    );
                    scene.lights.insert(
                        scene.lights.end(),
                        std::make_move_iterator(importedScene.lights.begin()),
                        std::make_move_iterator(importedScene.lights.end())
                    );
                }
            } else if (imports.isScalar()) {
                std::string importFile = imports;
                std::filesystem::path importPath = basePath.empty() ? std::filesystem::path(importFile) : std::filesystem::path(basePath) / importFile;
                raytracer::Scene importedScene = parseFile(importPath.string());
                scene.primitives.insert(
                    scene.primitives.end(),
                    std::make_move_iterator(importedScene.primitives.begin()),
                    std::make_move_iterator(importedScene.primitives.end())
                );
                scene.lights.insert(
                    scene.lights.end(),
                    std::make_move_iterator(importedScene.lights.begin()),
                    std::make_move_iterator(importedScene.lights.end())
                );
            }
        }
        if (cfg.exists("camera")) parseCamera(cfg.lookup("camera"), scene);
        if (cfg.exists("primitives")) parsePrimitives(cfg.lookup("primitives"), scene);
        if (cfg.exists("lights")) parseLights(cfg.lookup("lights"), scene);
    }

    void Parser::parseCamera(const libconfig::Setting &setting, raytracer::Scene &scene)
    {
        setting["resolution"].lookupValue("width", scene.imageWidth);
        setting["resolution"].lookupValue("height", scene.imageHeight);
        math::Point3D origin(setting["position"]["x"], setting["position"]["y"], setting["position"]["z"]); 
        math::Point3D lookAt(0, 0, 0);
        if (setting.exists("lookAt")) {
             setting["lookAt"].lookupValue("x", lookAt.x);
             setting["lookAt"].lookupValue("y", lookAt.y);
             setting["lookAt"].lookupValue("z", lookAt.z);
        }
        double fov = 90.0;
        setting.lookupValue("fieldOfView", fov);
        double aspectRatio = static_cast<double>(scene.imageWidth) / scene.imageHeight;
        scene.camera = raytracer::Camera(origin, lookAt, math::Vector3D(0, 1, 0), fov, aspectRatio);
        // scene.camera = raytracer::Camera(origin, fov, scene.imageWidth, scene.imageHeight);
    }

    void Parser::parsePrimitives(const libconfig::Setting &setting, raytracer::Scene &scene)
    {
        raytracer::Factory factory;

        if (setting.exists("spheres")) {
            for (const auto &config : setting["spheres"]) {
                math::Point3D center(config["x"], config["y"], config["z"]);
                double radius = config["r"];
                raytracer::Color color(config["color"]["r"], config["color"]["g"], config["color"]["b"]);
                
                scene.primitives.push_back(factory.createSphere(center, radius, color));
            }
        }
        if (setting.exists("planes")) {
            for (const auto &config : setting["planes"]) {
                std::string axis = static_cast<std::string>(config["axis"]);
                double position = config["position"];
                raytracer::Color color(config["color"]["r"], config["color"]["g"], config["color"]["b"]);
                
                scene.primitives.push_back(factory.createPlane(axis, position, color));
            }
        }
    }

    void Parser::parseLights(const libconfig::Setting &setting, raytracer::Scene &scene)
    {
        raytracer::Factory factory;
        setting.lookupValue("ambient", scene.ambientLight);
        setting.lookupValue("diffuse", scene.diffuseLight);

        if (setting.exists("point")) {
            for (const auto &config : setting["point"]) {
                math::Point3D origin(config["origin"]["x"], config["origin"]["y"], config["origin"]["z"]);
                raytracer::Color color(config["color"]["r"], config["color"]["g"], config["color"]["b"]);

                scene.lights.push_back(factory.createPointLight(origin, color));
            }
        }
        if (setting.exists("directional")) {
             for (const auto &config : setting["directional"]) {
                math::Vector3D direction(config["direction"]["x"], config["direction"]["y"], config["direction"]["z"]);
                raytracer::Color color(config["color"]["r"], config["color"]["g"], config["color"]["b"]);

                scene.lights.push_back(factory.createDirectionalLight(direction, color));
            }
        }
    }
}