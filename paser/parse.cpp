/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** parsing
*/

#include "parser.hpp"
#include "Primitive_fact.hpp"
#include "ErrorHandler.hpp"

Parser::Parser(const std::string& filename, ErrorHandler& errorHandler)
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

bool Parser::parse(Scene& scene)
{
    if (errors_.hasErrors())
        return false;
    return parseCamera(scene)
        && parseLights(scene)
        && parsePrimitives(scene);
}

bool Parser::parseCamera(Scene& scene)
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
