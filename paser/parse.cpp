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