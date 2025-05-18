/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Raytracer.hpp
*/

#pragma once
#include "scene/Image.hpp"
#include "scene/Scene.hpp"
// #include "SceneParser.hpp"
#include <filesystem>
#include "Error.hpp"
#include <iostream>
#include <fstream>

namespace core {
    class RayTracer {
        public:
            RayTracer(const int ac, char **const av)
                : _ac(ac), _av(av) {}
            ~RayTracer() = default;

            void help() const;
            int run() const;
        private:
            int _ac;
            char **_av;
    };
}