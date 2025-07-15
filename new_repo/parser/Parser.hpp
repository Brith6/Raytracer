/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Parser.hpp
*/

#pragma once

#include "../core/scene/Scene.hpp"
#include <string>

namespace libconfig {
    class Config;
    class Setting;
}

namespace core {
    class Parser {
    public:
        static raytracer::Scene parseFile(const std::string &filename);

    private:
        Parser() = default;

        static void processConfig(const libconfig::Config &cfg, raytracer::Scene &scene, const std::string &basePath);
        static void parseCamera(const libconfig::Setting &setting, raytracer::Scene &scene);
        static void parsePrimitives(const libconfig::Setting &setting, raytracer::Scene &scene);
        static void parseLights(const libconfig::Setting &setting, raytracer::Scene &scene);
    };
}