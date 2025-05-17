/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** parsing
*/
#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "ErrorHandler.hpp"
#include "Scene.hpp"
#include <libconfig.h++>

namespace raytracer{
    class Parser {
public:
    Parser(const std::string& filename, ErrorHandler& errorHandler);
    bool parse(Scene& scene);
private:
    bool parseCamera(Scene& scene);
    bool parseLights(Scene& scene);
    bool parsePrimitives(Scene& scene);
    libconfig::Config cfg_;
    ErrorHandler& errors_;
};
}

#endif
